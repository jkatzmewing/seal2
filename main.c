#include <stdio.h>
#include <windows.h>
#include "seal2.h"

int main(int argc, char *argv[])
{
	int i = 1;
	int restrictions = 0;
	
	if (argc < 2)
	{
		printf("%s\n", "Usage: seal2.exe [--gui] <\"Path\\To\\Executable arg1 arg2 ...\">");
		exit(0);
	}
	
	for (; i < argc - 1; i++)
	{
		char test_str[] = "--gui";
		if (0 == strncmp(test_str, argv[i], sizeof(test_str) - 1)) {
			restrictions |= RESTRICT_GUI;
		}
	}
	
	return seal2_launch(restrictions, argv[argc - 1]);
}
