#ifndef IMG_WINDOW
#define IMG_WINDOW

#include <stdio.h>
#include <stdbool.h>

#define CV_IGNORE_DEBUG_BUILD_GUARD
#include <opencv2/highgui/highgui_c.h>
#include <opencv2/imgcodecs/imgcodecs_c.h>

#include "frame.h"

void play(const char* windowName, FrameNode* head);

#endif