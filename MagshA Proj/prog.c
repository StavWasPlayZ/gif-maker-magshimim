/*********************************
* Class: MAGSHIMIM C2			 *
* openCV template      			 *
**********************************/

#include "cmd.h"

int main(void)
{
	Configs* configs = promptWelcome();

	while (promptCmdMenu(configs));

	return 0;
}