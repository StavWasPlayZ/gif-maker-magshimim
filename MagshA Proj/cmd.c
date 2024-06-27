#include "cmd.h"

Configs* _handleLoadProj(void);
Configs* _handleNewProj(void);

void _handleNewFrame(Configs* configs);
void _handleRemoveFrame(Configs* configs);
void _handleChangeFrameIndex(Configs* configs);
void _handleChangeFrameDuration(Configs* configs);
void _handleChangeFrameDurationAll(Configs* configs);
void _handleListFrames(Configs* configs);
void _handlePlay(Configs* configs);
void _handleSaveProj(Configs* configs);
void _handleExit(Configs* configs);

void _handleReverse(Configs* configs);
void _handleExportFrame(Configs* configs);


const char* const gifWindowName = "GIF display";

/*
Prompts the welcome screen; will ask the
user for a project file.
Returns: The configs to be used throughout the program
*/
Configs* promptWelcome(void)
{
	while (true)
	{
		printf("Welcome to Magshimim Movie Maker! what would you like to do?\n");
		printf(" [0] Create a new project\n");
		printf(" [1] Load existing project\n");

		switch (iInput())
		{
			case 0: return _handleNewProj();
			case 1: return _handleLoadProj();
		}
	}
}

Configs* _handleLoadProj(void)
{
	char path[STR_LEN] = { 0 };
	printf("Enter the path of the project (including project name): ");
	input(path, STR_LEN);

	Configs* configs = loadConfigs(path);
	if (configs == NULL)
	{
		// Error likely already printed
		_handleNewProj();
		return;
	}

	printf("Project loaded successfully\n");
	return configs;
}
Configs* _handleNewProj(void)
{
	printf("Working on a new project\n");
	FrameNode* head = createFrameNode(NULL);

	const char* rootPath = NULL;
	while (true)
	{
		char* buffer[STR_LEN] = { 0 };
		printf("Enter working directory path: ");
		input(buffer, STR_LEN);
		rootPath = statToDyn(buffer);

		if (dirExists(rootPath))
		{
			promptLoadAll(rootPath, head);
		}
		else
		{
			printf("Directory does not exist!\n");
			continue;
		}

		break;
	}

	return createNewConfig(rootPath, head);
}

/*
Prompts the user to load all images
from the provided directory
*/
void promptLoadAll(const char* const path, FrameNode* head)
{
	while (true)
	{
		printf("Would you like to load all images from %s into the project? (Y/N): ", path);
	
		char answer[2] = { 0 };
		input(answer, 2);

		answer[0] = tolower(answer[0]);
		switch (answer[0])
		{
			case 'y':
			{
				printf("Enter collective duration for all images: ");
				int duration = iInput();

				printf("Reading images...\n");

				int imgCount = 0;
				char** images = collectAllImages(path, &imgCount);
				qsort(images, imgCount, sizeof(char*), abcComp);

				printf("Loading %d images...\n", imgCount);
				loadAllImages(images, imgCount, duration, head);

				free(images); // We need the paths within; not the array itself.
				return;
			}
			case 'n':
				return;
		}
	}
}


/*
Prompts the main command menu.
Input: The frames list to act upon
Returns: Whether the program should be kept alive
*/
bool promptCmdMenu(Configs* configs)
{
	printf("\nWhat would you like to do?\n");
	printf(" [0] Exit\n");
	printf(" [1] Add new Frame\n");
	printf(" [2] Remove a Frame\n");
	printf(" [3] Change frame index\n");
	printf(" [4] Change frame duration\n");
	printf(" [5] Change duration of all frames\n");
	printf(" [6] List frames\n");
	printf(" [7] Play movie!\n");
	printf(" [8] Save project\n");
	printf(" [9] Reverse frames\n");
	printf(" [10] Apply Filters\n");
	printf(" [11] Export frame\n");

	switch (iInput())
	{
		case 0: _handleExit(configs); return false;
		case 1: _handleNewFrame(configs); break;
		case 2: _handleRemoveFrame(configs); break;
		case 3: _handleChangeFrameIndex(configs); break;
		case 4: _handleChangeFrameDuration(configs); break;
		case 5: _handleChangeFrameDurationAll(configs); break;
		case 6: _handleListFrames(configs); break;
		case 7: _handlePlay(configs); break;
		case 8: _handleSaveProj(configs); break;
		case 9: _handleReverse(configs); break;
		case 10: while (promptFiltersMenu(configs)); break;
		case 11: _handleExportFrame(configs); break;
	}

	return true;
}

void _handleNewFrame(Configs* configs)
{
	printf("\n***Creating new frame***\n");
	char buffer[STR_LEN] = { 0 };

	const char* path = NULL;
	IplImage* img = NULL;
	while (true)
	{
		inputPath(configs->rootPath, buffer, "Frame path: ");

		path = statToDyn(buffer);
		img = cvLoadImage(path, 1);

		if (img == NULL)
		{
			fprintf(stderr, "Could not open image %s\n", path);
			continue;
		}
		break;
	}

	printf("Frame duration (ms): ");
	int duration = iInput();

	printf("Please choose a name for that frame: ");
	input(buffer, STR_LEN);
	const char* name = statToDyn(buffer);

	appendFrame(configs->framesList, createFrame(name, duration, path, img));
}
void _handleRemoveFrame(Configs* configs)
{
	char name[STR_LEN] = { 0 };
	printf("Enter the name of the frame you wish to erase: ");
	input(name, STR_LEN);

	if (remFrameNodeByName(name, configs->framesList))
	{
		printf("Frame removed successfully\n");
	}
	else
	{
		printf("The frame was not found\n");
	}
}
void _handleChangeFrameIndex(Configs* configs)
{
	int len = framesLen(configs->framesList);
	int index = 0;

	while (true)
	{
		printf("Enter the new index in the movie you wish to place the frame: ");
		index = iInput();

		if (index > len)
		{
			fprintf(stderr, "The movie contains only %d frames!\n", len);
			continue;
		}

		break;
	}

	char name[STR_LEN] = { 0 };
	printf("Enter the name of the frame: ");
	input(name, STR_LEN);

	if (setFrameIndex(name, index, configs->framesList))
	{
		printf("Index changed successfully\n");
	}
	else
	{
		printf("This frame does not exist\n");
	}
}
void _handleChangeFrameDuration(Configs* configs)
{
	char name[STR_LEN] = { 0 };
	printf("Enter the name of the frame: ");
	input(name, STR_LEN);

	FrameNode* frameNode = frameNodeByName(name, configs->framesList);
	if (frameNode == NULL)
	{
		fprintf(stderr, "The frame does not exist\n");
		return;
	}

	int duration = 0;
	while (duration <= 0)
	{
		printf("Enter the new duration: ");
		duration = iInput();
	}

	frameNode->frame->durationMs = duration;

	printf("Duration changed successfully\n");
}
void _handleChangeFrameDurationAll(Configs* configs)
{
	int duration = 0;
	while (duration <= 0)
	{
		printf("Enter the duration of all frames: ");
		duration = iInput();
	}

	FrameNode* curr = configs->framesList->next;
	while (curr->frame != NULL)
	{
		curr->frame->durationMs = duration;
		curr = curr->next;
	}

	printf("Durations changed successfully\n");
}
void _handleListFrames(Configs* configs)
{
	printFramesSummary(configs->framesList);
}
void _handlePlay(Configs* configs)
{
	printf("Playing movie...\nPress ESC to stop\n");
	play(gifWindowName, configs->framesList);
}
void _handleSaveProj(Configs* configs)
{
	char path[PATH_MAX] = { 0 };
	printf("*Note: Relative paths are relative to current directory\n");
	printf("Enter save location: ");
	input(path, PATH_MAX);

	if (saveConfigs(configs, path))
	{
		printf("Project successfully saved\n");
	}
}

void _handleExit(Configs* configs)
{
	freeConfigs(configs);
	printf("Bye!\n");
}


void _handleReverse(Configs* configs)
{
	reverseFramesList(configs->framesList);
	printf("Frames reveresed successfully");
}

void _handleExportFrame(Configs* configs)
{
	char name[STR_LEN] = { 0 };
	printf("Enter the name of the frame: ");
	input(name, STR_LEN);

	FrameNode* frame = frameNodeByName(name, configs->framesList);
	if (frame == NULL)
	{
		fprintf(stderr, "No such frame \"%s\"\n", name);
		return;
	}

	char path[PATH_MAX] = { 0 };
	inputPath(configs->rootPath, path, "Enter path to export: ");

	cvSaveImage(path, frame->frame->img, 0);

	printf("Image exported successfully to %s\n", path);
}
