#include "gif_window.h"

#define ESCAPE 27

bool _handleWindowKeyIn(char key);


// Re-wrote the frames struct and "play" function myself
// I want the program to actually cache in the images,
// so as to not constantly load them every so often.
// Also a good practice to familiarize myself with the API.

/*
Plays the provided "gif" frames in loops within the main window, until user interrupts.
*/
void play(const char* windowName, FrameNode* head)
{
	cvNamedWindow(windowName, CV_WINDOW_AUTOSIZE);

	bool keepAlive = true;

	do
	{
		head = head->next;
		if (head->frame == NULL)
			continue;

		cvShowImage(windowName, head->frame->img);

		keepAlive = _handleWindowKeyIn(cvWaitKey(head->frame->durationMs));
	} while (keepAlive);

	cvDestroyWindow(windowName);
}

/*
Handles the window's keyboard input.
Returns: Whether to keep the window alive
*/
bool _handleWindowKeyIn(char key)
{
	switch (key)
	{
		case ESCAPE: return false;
		// ..thought there would be more
	}

	return true;
}