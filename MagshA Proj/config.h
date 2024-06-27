#ifndef CONFIGH
#define CONFIGH

#define PATH_MAX 260

#include <stdio.h>

#define CV_IGNORE_DEBUG_BUILD_GUARD
#include <opencv2/imgcodecs/imgcodecs_c.h>

#include "frame.h"
#include "util.h"

typedef struct Configs
{
	const char* rootPath;
	FrameNode* framesList;
} Configs;

Configs* createNewConfig(const char* rootPath, FrameNode* framesList);
void freeConfigs(Configs* configs);

Configs* loadConfigs(const char* const path);
bool saveConfigs(const Configs* const configs, const char* const path);

#endif