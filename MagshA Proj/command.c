//#include "command.h"
//
//#define STR_LEN 256
//
//FrameNode* _handleLoadProj(void);
//FrameNode* _handleNewProj(void);
//
//void _handleNewFrame(FrameNode* head);
//void _handleRemoveFrame(FrameNode* head);
//void _handleChangeFrameIndex(FrameNode* head);
//void _handleChangeFrameDuration(FrameNode* head);
//void _handleChangeFrameDurationAll(FrameNode* head);
//void _handleListFrames(FrameNode* head);
//void _handlePlay(FrameNode* head);
//void _handleSaveProj(FrameNode* head);
//
//
//const char* gifWindowName = "GIF display";
//
///*
//Prompts the welcome screen; will ask the
//user for a project file.
//Returns: The frames list to be used throughout the program
//*/
//FrameNode* promptWelcome(void)
//{
//	while (true)
//	{
//		printf("Welcome to Magshimim Movie Maker! what would you like to do?\n");
//		printf(" [0] Create a new project\n");
//		printf(" [1] Load existing project\n");
//
//		switch (iInput())
//		{
//		case 0: return _handleNewProj();
//		case 1: return _handleLoadProj();
//		}
//	}
//}
//
//FrameNode* _handleLoadProj(void)
//{
//	char path[STR_LEN] = { 0 };
//	printf("Enter the path of the project (including project name): ");
//	input(path, STR_LEN);
//
//	//TODO implement
//
//	printf("Project loaded successfully\n");
//	return createFrameNode(NULL);
//}
//FrameNode* _handleNewProj(void)
//{
//	printf("Working on a new project\n");
//	return createFrameNode(NULL);
//}
//
//
///*
//Prompts the main command menu.
//Input: The frames list to act upon
//Returns: Whether the program should be kept alive
//*/
//bool promptCmdMenu(FrameNode* head)
//{
//	printf("\nWhat would you like to do?\n");
//	printf(" [0] Exit\n");
//	printf(" [1] Add new Frame\n");
//	printf(" [2] Remove a Frame\n");
//	printf(" [3] Change frame index\n");
//	printf(" [4] Change frame duration\n");
//	printf(" [5] Change duration of all frames\n");
//	printf(" [6] List frames\n");
//	printf(" [7] Play movie!\n");
//	printf(" [8] Save project\n");
//
//	switch (iInput())
//	{
//	case 0: return false;
//	case 1: _handleNewFrame(head); break;
//	case 2: _handleRemoveFrame(head); break;
//	case 3: _handleChangeFrameIndex(head); break;
//	case 4: _handleChangeFrameDuration(head); break;
//	case 5: _handleChangeFrameDurationAll(head); break;
//	case 6: _handleListFrames(head); break;
//	case 7: _handlePlay(head); break;
//	case 8: _handleSaveProj(head); break;
//	}
//
//	return true;
//}
//
//void _handleNewFrame(FrameNode* head)
//{
//	printf("***Creating new frame***\n");
//	char buffer[STR_LEN] = { 0 };
//
//	const char* path = NULL;
//	IplImage* img = NULL;
//	while (true)
//	{
//		printf("Frame path: ");
//		input(buffer, STR_LEN);
//
//		path = statToDyn(buffer);
//		img = cvLoadImage(path, 1);
//
//		if (img == NULL)
//		{
//			fprintf(stderr, "Could not open image %s\n", path);
//			continue;
//		}
//		break;
//	}
//
//	printf("Frame duration (ms): ");
//	int duration = iInput();
//
//	printf("Please choose a name for that frame: ");
//	input(buffer, STR_LEN);
//	const char* name = statToDyn(buffer);
//
//	addFrame(head, createFrame(name, duration, path, img));
//}
//void _handleRemoveFrame(FrameNode* head)
//{
//
//}
//void _handleChangeFrameIndex(FrameNode* head)
//{
//
//}
//void _handleChangeFrameDuration(FrameNode* head)
//{
//
//}
//void _handleChangeFrameDurationAll(FrameNode* head)
//{
//
//}
//void _handleListFrames(FrameNode* head)
//{
//
//}
//void _handlePlay(FrameNode* head)
//{
//	play(gifWindowName, head);
//}
//void _handleSaveProj(FrameNode* head)
//{
//
//}
