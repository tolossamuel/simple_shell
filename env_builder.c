#include "shell.h"

/**
 * env_builders - a function that searches for a matching string
 * in a predefined array
 * @arv: is a character array pointer
 * Return: a function pointer or NULL
 */
CommandFunction env_builders(char **arv)
{
	int num1, num2;
	CommandFunction result = NULL;
	env_structure menu_list[] = {
		{"exit", exit_cmd},
	};

	for (num1 = 0; menu_list[num1].built_in; num1++)
	{
		num2 = 0;
		if (menu_list[num1].built_in[num2] == arv[0][num2])
		{
			for (num2 = 0; arv[0][num2]; num2++)
			{
				if (menu_list[num1].built_in[num2] != arv[0][num2])
					break;
			}
			if (!arv[0][num2])
			{
				result = menu_list[num1].function;
				break;
			}
		}
	}
	return (result);
}

/**
 * exit_cmd -  frees the and exit the program
 * @arr:  parameter and exits the program
 * Return: Nothing void functions
*/
void exit_cmd(char **arr)
{
	free(arr);
	exit(0);
}
