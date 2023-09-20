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
	if (arv == NULL || arv[0] == NULL)
		return (NULL);
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

/**
 * check_file_status - checks the status of a file's content based
 * on its size, and if the size is -1 (indicating an error)
 * it frees the content and exits the program if the input is
 * from a terminal
 * @size: The size parameter indicates the size of the file's content
 * @content: The content parameter is a pointer to the file's content
 * which is freed if the size is -1
 * Return: nothing it is void functions
*/
void check_file_status(int size, char *content)
{
	(void)content;
	if (size == -1)
	{
		if (isatty(STDIN_FILENO))
		{
			free(content);
		}
		exit(0);
	}
}
