#ifndef FILTERS_H
#define FILTERS_H

#include <stdbool.h>

#define CV_IGNORE_DEBUG_BUILD_GUARD
#include <opencv2/core/core_c.h>
#include <opencv2/highgui/highgui_c.h>
#include <opencv2/imgcodecs/imgcodecs_c.h>

#include "config.h"

bool promptFiltersMenu(Configs* configs);

#endif
