#include "shell.h"

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
void tokenize_data(program_info *info)
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
		perror(info->Name_projects);
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