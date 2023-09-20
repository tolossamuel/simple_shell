#include "shell.h"

/**
 * logical_operations - splits a command array into subcommands based
 * on logical operators
 * @cmd_array: An array of strings (commands)
 * @num: An integer representing the current position in the cmd_array
 * @ops_ary: An array of characters used to store the logical operators
 * Return: the number of subcommands created from the input command array
 */
int logical_operations(char *cmd_array[], int num, char ops_ary[])
{
	int num1;
	char *temporary = NULL;

	for (num1 = 0; cmd_array[num] != NULL  && cmd_array[num][num1]; num1++)
	{
		if (cmd_array[num][num1] == '&' && cmd_array[num][num1 + 1] == '&')
		{
			temporary = cmd_array[num];
			cmd_array[num][num1] = '\0';
			cmd_array[num] = string_repetitions(cmd_array[num]);
			cmd_array[num + 1] = string_repetitions(temporary + num1 + 2);
			num++;
			ops_ary[num] = '&';
			free(temporary);
			num1 = 0;
		}
		if (cmd_array[num][num1] == '|' && cmd_array[num][num1 + 1] == '|')
		{
			temporary = cmd_array[num];
			cmd_array[num][num1] = '\0';
			cmd_array[num] = string_repetitions(cmd_array[num]);
			cmd_array[num + 1] = string_repetitions(temporary + num1 + 2);
			num++;
			ops_ary[num] = '|';
			free(temporary);
			num1 = 0;
		}
	}
	return (num);
}

/**
 * tokenize_data - The function tokenize an input string, stores
 * tokens in info->tokens, and sets the command name in info->cmd_name
 * @info: parameter in these functions stores information and
 * performs operations related to the program's data and execution
 * Return: The function doesn't return a value (void)
 */
void tokenize_data(about_info *info)
{
	char *limiter = " \t";
	int num1, num2, counter = 2, length;

	length = string_size(info->get_line);
	if (length)
	{
		if (info->get_line[length - 1] == '\n')
			info->get_line[length - 1] = '\0';
	}
	for (num1 = 0; info->get_line[num1]; num1++)
	{
		for (num2 = 0; limiter[num2]; num2++)
		{
			if (info->get_line[num1] == limiter[num2])
				counter++;
		}
	}
	info->tokens = malloc(counter * sizeof(char *));
	if (info->tokens == NULL)
	{
		perror(info->name_projects);
		exit(errno);
	}
	num1 = 0;
	info->tokens[num1] = string_repetitions(str_tok(info->get_line, limiter));
	info->cmd_name = string_repetitions(info->tokens[0]);
	while (info->tokens[num1++])
	{
		info->tokens[num1] = string_repetitions(str_tok(NULL, limiter));
	}
}
