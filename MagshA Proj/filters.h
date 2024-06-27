#ifndef FILTERS_H
#define FILTERS_H

#include <stdbool.h>

#define CV_IGNORE_DEBUG_BUILD_GUARD
#include <opencv2/core/core_c.h>
#include <opencv2/highgui/highgui_c.h>
#include <opencv2/imgcodecs/imgcodecs_c.h>

#include "config.h"

typedef void (*FilterApplier)(Configs*, Frame*);

bool promptFiltersMenu(Configs* configs);

void applyBinaryFilter(Configs* configs);
void applyBlurFilter(Configs* configs);

#endif
