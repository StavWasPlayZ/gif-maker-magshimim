#ifndef LINKEDLISTH
#define LINKEDLISTH

#define CV_IGNORE_DEBUG_BUILD_GUARD
#include <opencv2/core/core_c.h>
#include <stdio.h>

typedef struct Frame
{
	// why not just indexes...
	const char* name;
	unsigned int durationMs;
	const char* path;
	IplImage* img;
	// A set of flags indicating which filters are enabled
	// I'm turning in the work in a few minutes
	// so I kinda have to rush this
	// Known issue: the filters are always applied in
	// a hard-coded order
	unsigned int filters;
} Frame;

typedef struct FrameNode
{
	Frame* frame;
	struct FrameNode* next;
} FrameNode;


Frame* createFrame(const char* name, unsigned int duration, const char* path, IplImage* img, unsigned int filters);
FrameNode* createFrameNode(Frame* frame);
void printFramesSummary(FrameNode* head);
FrameNode* reverseFramesList(FrameNode* head);
FrameNode* appendFrame(FrameNode* head, Frame* frame);
FrameNode* insertFrameAtCurrent(FrameNode* node, Frame* frame);
FrameNode* frameTail(FrameNode* head);
FrameNode* frameNodeByName(const char* const name, FrameNode* head);
FrameNode* frameNodeByNameBef(const char* const name, FrameNode* head);
bool remFrameNodeByName(const char* const name, FrameNode* head);
bool setFrameIndex(const char* const name, const int index, FrameNode* head);
int framesLen(FrameNode* head);
void freeFramesList(FrameNode* head);
void freeFrame(Frame* frame);

#endif
