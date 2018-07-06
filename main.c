#include <stdio.h>
#include <windows.h>
#include "seal2.h"

int main(int argc, char *argv[])
{
	int i = 1;
	int restrictions = 0;
	
	if (argc < 2)
	{
		printf("%s\n", "Usage: seal2.exe [--gui] [--gui-light] <\"Path\\To\\Executable arg1 arg2 ...\">");
		exit(0);
	}
	
	for (; i < argc - 1; i++)
	{
		const char arg_gui[] = "--gui";
		const char arg_gui_light[] = "--gui-light";

		if (0 == strncmp(arg_gui, argv[i], sizeof(arg_gui) - 1)) {
			restrictions |= RESTRICT_GUI;
		}
		else if (0 == strncmp(arg_gui_light, argv[i], sizeof(arg_gui_light) - 1)) {
			restrictions |= RESTRICT_GUI_LIGHT
		}
	}
	
	return seal2_launch(restrictions, argv[argc - 1]);
}
