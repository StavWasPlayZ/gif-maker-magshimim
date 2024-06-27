#include "util.h"

/*
Awaits for a string to be entered in
the input stream, then saves it into the provided buffer.
*/
void input(char* buffer, int strLen)
{
	fgets(buffer, strLen, stdin);
	buffer[strcspn(buffer, "\n")] = 0;
}

/*
Returns: The entered integer from the input stream.
*/
int iInput(void)
{
	int answer = 0;
	scanf_s("%d", &answer);
	getchar();

	return answer;
}

/*
Gets a string path from the user, and concatinates it with
the selected Working Directory folder (if applicable).
Puts it into the provided buffer; prints the given message.
*/
void inputPath(const char* const workingDir, char* const buffer, const char* const message)
{
	printf("*Note: Prefix './' to locate relative to working directory path\n");
	printf("%s", message);
	input(buffer, STR_LEN);

	if (strncmp(buffer, "./", 2) == 0)
	{
		//memset(buffer, 0, STR_LEN);
		char relativeAfter[STR_LEN] = { 0 };
		strncpy_s(relativeAfter, STR_LEN, buffer + 2, STR_LEN);

		snprintf(buffer, STR_LEN, "%s/%s", workingDir, relativeAfter);
	}
}


/*
Converts a static buffer into a dynamic one
Returns: The dynamic buffer
*/
char* statToDyn(const char* buffer)
{
	int len = strlen(buffer);
	char* result = (char*)malloc(sizeof(char) * (len + 1));
	strncpy_s(result, len + 1, buffer, len + 1);

	return result;
}

bool endsWith(const char* const subject, const char* const str)
{
	int subjLen = strlen(subject);
	int strLen = strlen(str);

	if (strLen > subjLen)
		return false;

	return strncmp(&subject[strLen - subjLen], str, strLen);
}

/*
A comparison function for sorting string arrays by ASCII values.
*/
int abcComp(const void* str1, const void* str2)
{
	return strcmp(*(const char**)str1, *(const char**)str2);
}

/*
Returns: The index of the last occurence of `chara`,
or -1 if not found.
*/
int lastIndexOf(const char* const str, const char chara)
{
	//TODO: Replace all usages with strrchr
	int len = strlen(str);

	int i = 0;
	for (i = len; i >= 0; i--)
	{
		if (str[i] == chara)
		{
			return i;
		}
	}

	return -1;
}
