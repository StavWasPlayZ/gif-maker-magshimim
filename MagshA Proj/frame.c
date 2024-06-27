#include "frame.h"

// Note: The frame node list is circular, and
// determines the starting point with the null head.

/*
Constructs a new frame struct instance.
*/
Frame* createFrame(const char* name, unsigned int duration, const char* path, IplImage* img)
{
	Frame* frame = (Frame*)malloc(sizeof(Frame));
	frame->name = name;
	frame->durationMs = duration;
	frame->path = path;
	frame->img = img;
	return frame;
}

/*
Constructs a new frame node instance.
Input: The frame; nullable
*/
FrameNode* createFrameNode(Frame* frame)
{
	FrameNode* node = (FrameNode*)malloc(sizeof(FrameNode));
	node->frame = frame;
	node->next = node;
	return node;
}


/*
Adds the provided frame to the end of the given node list
Returns: The newly created frame node
*/
FrameNode* appendFrame(FrameNode* head, Frame* frame)
{
	return insertFrameAtCurrent(frameTail(head), frame);
}

/*
Inserts the given frame right after the provided node.
Returns: The newly created frame node
*/
FrameNode* insertFrameAtCurrent(FrameNode* node, Frame* frame)
{
	FrameNode* newNode = createFrameNode(frame);
	FrameNode* oldNext = node->next;

	node->next = newNode;
	newNode->next = oldNext;

	return newNode;
}


/*
Returns: The tail of the given node list
*/
FrameNode* frameTail(FrameNode* head)
{
	// If only I was allowed to use doubly linked lists...
	while (head->next->frame != NULL)
	{
		head = head->next;
	}

	return head;
}

/*
Returns: The node matching the provided name within the given frames list,
or null if not found.
*/
FrameNode* frameNodeByName(const char* const name, FrameNode* head)
{
	head = head->next;
	while (head->frame != NULL)
	{
		if (strcmp(name, head->frame->name) == 0)
		{
			return head;
		}

		head = head->next;
	}

	return NULL;
}

/*
Returns: The node before the specified frame's name,
or null if not found.
*/
FrameNode* frameNodeByNameBef(const char* const name, FrameNode* head)
{
	while (head->next->frame != NULL)
	{
		if (strcmp(name, head->next->frame->name) != 0)
		{
			head = head->next;
			continue;
		}

		return head;
	}

	return NULL;
}


/*
Removes the frame by name from the provided list
Returns: Whether the operation was successful
*/
bool remFrameNodeByName(const char* const name, FrameNode* head)
{
	head = frameNodeByNameBef(name, head);
	if (head == NULL)
		return false;

	FrameNode* newNext = head->next->next;
	freeFrame(head->next->frame);
	free(head->next);

	head->next = newNext;
	
	return true;
}

/*
Sets the index of the provided frame's name to the given index.
Returns: Whether the operation was successful
*/
bool setFrameIndex(const char* const name, const int index, FrameNode* head)
{
	FrameNode* desiredNodeBef = frameNodeByNameBef(name, head);
	if (desiredNodeBef == NULL)
		return false;

	int i = 0;
	while (i != index - 1)
	{
		head = head->next;
		i++;
	}

	FrameNode* desiredNode = desiredNodeBef->next;
	FrameNode* desiredNodeAfter = desiredNode->next;
	FrameNode* destNode = head->next;

	head->next = desiredNode;
	desiredNode->next = destNode;
	desiredNodeBef->next = desiredNodeAfter;

	return true;
}

/*
Returns: The length of the list
*/
int framesLen(FrameNode* head)
{
	int result = 0;

	head = head->next;
	while (head->frame != NULL)
	{
		result++;
		head = head->next;
	}

	return result;
}


/*
Prints all items of the provided frames node list
*/
void printFramesSummary(FrameNode* head)
{
	head = head->next;
	int i = 0;

	printf("\t%s\t%-20s%-20s%-20s\n", "Index", "Name", "Duration", "Path");
	while (head->frame != NULL)
	{
		Frame* frame = head->frame;

		char durationStr[21] = { 0 };
		sprintf_s(durationStr, 21, "%dms", frame->durationMs);
		printf("\t%5d\t%-20s%-20s%-20s\n", i + 1, frame->name, durationStr, frame->path);

		head = head->next;
		i++;
	}
}


/*
Reverses the given frame list
Returns: This list
*/
FrameNode* reverseFramesList(FrameNode* head)
{
	if (head->next->frame == NULL)
	{
		return head;
	}

	FrameNode* tailOld = reverseFramesList(head->next);

	head->next->next = head;
	if (head->frame == NULL)
	{
		// The old tail becomes the new head.
		head->next = tailOld;
		return head;
	}

	return tailOld;
}


/*
Deep-frees the provided frame list
*/
void freeFramesList(FrameNode* head)
{
	head = head->next;

	while (head->frame != NULL)
	{
		FrameNode* next = head->next;

		freeFrame(head->frame);
		free(head);

		head = next;
	}

	free(head);
}

/*
Frees the provided frame object
*/
void freeFrame(Frame* frame)
{
	cvReleaseImage(&(frame->img));
	free(frame->name);
	free(frame->path);
	free(frame);
}