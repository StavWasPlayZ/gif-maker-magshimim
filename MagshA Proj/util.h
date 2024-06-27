#ifndef UTILH
#define UTILH

#define STR_LEN 260

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

void input(char* buffer, int strLen);
int iInput(void);

void inputPath(const char* const workingDir, char* const buffer, const char* const message);


// String utils

char* statToDyn(const char* buffer);
bool endsWith(const char* const subject, const char* const str);
int abcComp(const void* str1, const void* str2);
int lastIndexOf(const char* const str, const char chara);

#endif