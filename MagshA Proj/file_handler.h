#ifndef FILE_HANDLERH
#define FILE_HANDLERH

#define PATH_MAX 260

#include <stdbool.h>

#define CV_IGNORE_DEBUG_BUILD_GUARD
#include <opencv2/imgcodecs/imgcodecs_c.h>
#include "util.h"
#include "frame.h"
#include "dirent.h"

bool dirExists(const char* path);
char** collectAllImages(const char* const path, int* countOut);
void loadAllImages(const char** const images, const int imgCount, const duration, FrameNode* head);
bool isImage(const char* const path);

extern const char* const imgFileExts[];

#endif
