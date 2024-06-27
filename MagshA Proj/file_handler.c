#include "file_handler.h"

#define ASSUMED_FILES_IN_DIR 50

/*
Checks if the provided path can be opened as a directory.
*/
bool dirExists(const char* path)
{
	DIR* dir = opendir(path);
	if (dir == NULL)
	{
		return false;
	}

	closedir(dir);
	return true;
}

/*
Input: An integer buffer to store the amount of images
put into the returned array
Returns: An array of all image paths in the provided directory.
The provided resources should be freed.
*/
char** collectAllImages(const char* const path, int* countOut)
{
	DIR* dir = opendir(path);
	if (dir == NULL)
	{
		fprintf(stderr, "Error opening directory %s!", path);
		return false;
	}

	int capacity = ASSUMED_FILES_IN_DIR;
	char** images = (char**)malloc(sizeof(char*) * capacity);
	int imgCount = 0;

	struct dirent* curr = NULL;
	while ((curr = readdir(dir)) != NULL)
	{
		if (curr->d_type != DT_REG || !isImage(curr->d_name))
			continue;

		char fPath[PATH_MAX] = { 0 };
		sprintf_s(fPath, PATH_MAX, "%s/%s", path, curr->d_name);

		if (imgCount == capacity)
		{
			// Will overflow; increase capacity
			capacity += ASSUMED_FILES_IN_DIR;
			char** imagesNew = (char**)realloc(images, sizeof(char*) * capacity);

			if (imagesNew == NULL)
			{
				fprintf(stderr, "Not enough memory to load all images!\n");

				free(images);
				closedir(dir);
				return false;
			}

			images = imagesNew;
		}

		images[imgCount] = statToDyn(fPath);
		imgCount++;
	}

	closedir(dir);

	*countOut = imgCount;
	return images;
}

/*
Loads all images into the provided head.
Input: The images' path and the desired, collective duration of
all frames.
*/
void loadAllImages(const char** const images, const int imgCount, const duration, FrameNode* head)
{
	FrameNode* tail = frameTail(head);

	int i = 0;
	for (i = 0; i < imgCount; i++)
	{
		IplImage* img = cvLoadImage(images[i], 1);

		tail = insertFrameAtCurrent(tail, createFrame(
			// Convert to new dynamic string,
			// because freeing 2 instances
			// of the same string later will cause problems
			statToDyn(&images[i][lastIndexOf(images[i], '/') + 1]),
			duration,
			images[i], img, 0
		));
	}
}


const char* const imgFileExts[] = { ".jpg", ".jpeg", ".png" };

/*
Returns: Whether the provided file is of type
image
*/
bool isImage(const char* const path)
{
	int exts = sizeof(imgFileExts) / sizeof(char*);
	
	int i = 0;
	for (i = 0; i < exts; i++)
	{
		if (endsWith(path, imgFileExts[i]))
			return true;
	}

	return false;
}
