#include "config.h"

/*
Creates a new configs object
*/
Configs* createNewConfig(const char* rootPath, FrameNode* framesList)
{
	Configs* configs = (Configs*)malloc(sizeof(Configs));
	configs->rootPath = rootPath;
	configs->framesList = framesList;
	return configs;
}

/*
Deep-frees the provided configs object
*/
void freeConfigs(Configs* configs)
{
	freeFramesList(configs->framesList);
	free(configs->rootPath);
	free(configs);
}


// They said in the project file to "put these at a separate location".
// Here seems very reasonable.

/*
Loads all configurations from the provided config file.
Returns: The configurations opbject loaded from the provided path,
or null if could not.
*/
Configs* loadConfigs(const char* const path)
{
	FILE* file = NULL;

	fopen_s(&file, path, "r");
	if (file == NULL)
	{
		fprintf(stderr, "Could not open file %s", path);
		return NULL;
	}

	Configs* configs = (Configs*)malloc(sizeof(Configs));
	configs->framesList = createFrameNode(NULL);
	FrameNode* framesTail = configs->framesList;

	bool readWD = false;
	char line[PATH_MAX] = { 0 };
	while (fgets(line, PATH_MAX, file) != NULL)
	{
		line[strcspn(line, "\n")] = 0;

		if (!readWD)
		{
			configs->rootPath = statToDyn(line);
			readWD = true;
		}
		else
		{
			char imgPath[PATH_MAX] = { 0 };
			// 10 characters for 2^31
			char duration[11] = { 0 };
			char name[PATH_MAX] = { 0 };

			const int pathEndI = strchr(line, ',') - line;
			const int durationEndI = strchr(line + pathEndI + 1, ',') - line;

			if (pathEndI <= 0 || durationEndI <= 0)
			{
				fprintf(stderr, "Invalid file format for %s", path);
			}

			strncpy_s(imgPath, STR_LEN, line, pathEndI);
			strncpy_s(duration, 11, line + pathEndI + 1, durationEndI - pathEndI - 1);
			strncpy_s(name, STR_LEN, line + durationEndI + 1, STR_LEN);

			const IplImage* img = cvLoadImage(imgPath, 1);
			if (img == NULL)
			{
				fprintf(stderr, "Could not open image %s. Skipping...\n", imgPath);
				continue;
			}

			// I cannot check for atoi failing. It just returns 0, which is valid.
			framesTail = insertFrameAtCurrent(framesTail, createFrame(
				statToDyn(name), atoi(duration), statToDyn(imgPath), img
			));
		}
	}

	fclose(file);
	return configs;
}

/*
Saves the given configs into the provided file.
Returns: Whether the operation succeed.
*/
bool saveConfigs(const Configs* const configs, const char* const path)
{
	FILE* file = NULL;

	fopen_s(&file, path, "w");
	if (file == NULL)
	{
		fprintf(stderr, "Could not write to %s", path);
		return false;
	}

	fputs(configs->rootPath, file);

	FrameNode* curr = configs->framesList->next;
	while (curr->frame != NULL)
	{
		Frame* frame = curr->frame;
		fprintf(file, "\n%s,%d,%s", frame->path, frame->durationMs, frame->name);
		curr = curr->next;
	}

	fclose(file);
	return true;
}
