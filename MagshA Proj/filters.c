#include "filters.h"

void _handleBinaryFilter(Configs* configs);

/*
Prompts the filters selection menu
*/
bool promptFiltersMenu(Configs* configs)
{
	printf("\nWhich filters to apply?\n");
	printf(" [0] Return to Main Menu\n");
	printf(" [1] Black and White\n");
	printf(" [2] Blur\n");

	switch (iInput())
	{
		case 0: return false;
		case 1: _handleBinaryFilter(configs); break;
	}

	return true;
}

void _handleBinaryFilter(Configs* configs)
{
	FrameNode* node = configs->framesList->next;
	while (node->frame != NULL)
	{
		Frame* frame = node->frame;
		// Utilized: https://stackoverflow.com/a/1586352
		
		IplImage* im_rgb = frame->img;
		IplImage* im_gray = cvCreateImage(cvSize(im_rgb->width, im_rgb->height), im_rgb->depth, 1);
		cvCvtColor(im_rgb, im_gray, CV_RGB2GRAY);
		
		// Make it B&W:
		IplImage* im_bw = cvCreateImage(cvSize(im_gray->width, im_gray->height), im_gray->depth, 1);
		cvThreshold(im_gray, im_bw, 128, 255, CV_THRESH_BINARY | CV_THRESH_OTSU);

		frame->img = im_bw;
		node = node->next;
	}

	//TODO update configs
}
