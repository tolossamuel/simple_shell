#include "shell.h"

int logic_ops(char *cmd_array[], int num, char ops_ary[])
{
	
	int var;
	char *temporary = NULL;

	for (var = 0; cmd_array[num] != NULL  && cmd_array[num][var]; var++)
	{
		if (cmd_array[num][var] == '&' && cmd_array[num][var + 1] == '&')
		{
			temporary = cmd_array[num];
			cmd_array[num][var] = '\0';
			cmd_array[num] = string_repetitions(cmd_array[num]);
			cmd_array[num + 1] = string_repetitions(temporary + var + 2);
			num++;
			ops_ary[num] = '&';
			free(temporary);
			var = 0;
		}
		if (cmd_array[num][var] == '|' && cmd_array[num][var + 1] == '|')
		{
			temporary = cmd_array[num];
			cmd_array[num][var] = '\0';
			cmd_array[num] = string_repetitions(cmd_array[num]);
			cmd_array[num + 1] = string_repetitions(temporary + var + 2);
			num++;
			ops_ary[num] = '|';
			free(temporary);
			var = 0;
		}
	}
	return (num);
}
void tokenize_data(data_of_program *data)
{
	char *delimiter = " \t";
	int i, j, counter = 2, length;

	length = string_size(data->get_line);
	if (length)
	{
		if (data->get_line[length - 1] == '\n')
			data->get_line[length - 1] = '\0';
	}

	for (i = 0; data->get_line[i]; i++)
	{
		for (j = 0; delimiter[j]; j++)
		{
			if (data->get_line[i] == delimiter[j])
				counter++;
		}
	}

	data->tokens = malloc(counter * sizeof(char *));
	if (data->tokens == NULL)
	{
		perror(data->Name_projects);
		exit(errno);
	}
	i = 0;
	data->tokens[i] = string_repetitions(str_tok(data->get_line, delimiter));
	data->cmd_name = string_repetitions(data->tokens[0]);
	while (data->tokens[i++])
	{
		data->tokens[i] = string_repetitions(str_tok(NULL, delimiter));
	}
}