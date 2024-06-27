#include "filters.h"

#define BLUR_SIZE 15

void _handle_filter(Configs* config, FilterApplier applier);

/*
Prompts the filters selection menu
*/
bool promptFiltersMenu(Configs* configs)
{
	printf("\nWhich filters to apply?\n");
	printf(" [0] Return to Main Menu\n");
	printf(" [1] Black and White\n");
	printf(" [2] Blur\n");

	FilterApplier applier = NULL;

	switch (iInput())
	{
		case 0: return false;
		case 1: applier = applyBinaryFilter; break;
		case 2: applier = applyBlurFilter; break;
	}

	_handle_filter(configs, applier);

	return true;
}

/*
Handles applying the filter by the chosen function
*/
void _handle_filter(Configs* configs, FilterApplier applier)
{
	char frameName[STR_LEN] = { 0 };
	printf("Enter frame to apply filter to (leave blank for all): ");
	input(frameName, STR_LEN);

	if (strlen(frameName) == 0)
	{
		// Nothing chosen; apply for all
		FrameNode* node = configs->framesList->next;
		while (node->frame != NULL)
		{
			applier(configs, node->frame);
			node = node->next;
		}
	}
	else
	{
		FrameNode* frame = frameNodeByName(frameName, configs->framesList);
		if (frame == NULL)
		{
			fprintf(stderr, "No frame '%s' found", frameName);
			return;
		}

		applier(configs, frame->frame);
	}
}

void applyBinaryFilter(Configs* configs, Frame* frame)
{
	// Utilized: https://stackoverflow.com/a/1586352
		
	IplImage* im_rgb = frame->img;
	IplImage* im_gray = cvCreateImage(cvSize(im_rgb->width, im_rgb->height), im_rgb->depth, 1);
	cvCvtColor(im_rgb, im_gray, CV_RGB2GRAY);

	// Make it B&W:
	IplImage* im_bw = cvCreateImage(cvSize(im_gray->width, im_gray->height), im_gray->depth, 1);
	cvThreshold(im_gray, im_bw, 128, 255, CV_THRESH_BINARY | CV_THRESH_OTSU);

	cvReleaseImage(&im_rgb);
	cvReleaseImage(&im_gray);

	frame->img = im_bw;
	//TODO update config flags
}

void applyBlurFilter(Configs* configs, Frame* frame)
{
	IplImage* org = frame->img;
	IplImage* blurred = cvCreateImage(cvSize(org->width, org->height), org->depth, org->nChannels);
	cvSmooth(org, blurred, CV_GAUSSIAN, BLUR_SIZE, BLUR_SIZE, 0, 0); // not so sigma

	cvReleaseImage(&org);

	frame->img = blurred;
	//TODO update config flags
}
