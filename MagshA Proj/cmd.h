#ifndef COMMANDH
#define COMMANDH

#include "gif_window.h"
#include "config.h"
#include "file_handler.h"
#include "filters.h"

Configs* promptWelcome(void);
bool promptCmdMenu(Configs* head);
void promptLoadAll(const char* const path, FrameNode* head);

#endif