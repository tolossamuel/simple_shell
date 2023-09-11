#include "shell.h"

void var_expand(data_of_program *data)
{
	int i, j;
	char line[BUFFER_SIZE] = {0}, expansion[BUFFER_SIZE] = {'\0'}, *temp;

	if (data->get_line == NULL)
		return;
	new_buffer(line, data->get_line);
	for (i = 0; line[i]; i++)
		if (line[i] == '#')
			line[i--] = '\0';
		else if (line[i] == '$' && line[i + 1] == '?')
		{
			line[i] = '\0';
			string_long(errno, expansion, 10);
			new_buffer(line, expansion);
			new_buffer(line, data->get_line + i + 2);
		}
		else if (line[i] == '$' && line[i + 1] == '$')
		{
			line[i] = '\0';
			string_long(getpid(), expansion, 10);
			new_buffer(line, expansion);
			new_buffer(line, data->get_line + i + 2);
		}
		else if (line[i] == '$' && (line[i + 1] == ' ' || line[i + 1] == '\0'))
			continue;
		else if (line[i] == '$')
		{
			for (j = 1; line[i + j] && line[i + j] != ' '; j++)
				expansion[j - 1] = line[i + j];
			temp = get_key(expansion, data);
			line[i] = '\0', expansion[0] = '\0';
			new_buffer(expansion, line + i + j);
			temp ? new_buffer(line, temp) : 1;
			new_buffer(line, expansion);
		}
	if (!string_comparions(data->get_line, line, 0))
	{
		free(data->get_line);
		data->get_line = string_repetitions(line);
	}
}

void expand_alias(data_of_program *data)
{
	int i, j, was_expanded = 0;
	char line[BUFFER_SIZE] = {0}, expansion[BUFFER_SIZE] = {'\0'}, *temp;

	if (data->get_line == NULL)
		return;

	new_buffer(line, data->get_line);

	for (i = 0; line[i]; i++)
	{
		for (j = 0; line[i + j] && line[i + j] != ' '; j++)
			expansion[j] = line[i + j];
		expansion[j] = '\0';

		temp = get_fun(data, expansion);
		if (temp)
		{
			expansion[0] = '\0';
			new_buffer(expansion, line + i + j);
			line[i] = '\0';
			new_buffer(line, temp);
			line[string_size(line)] = '\0';
			new_buffer(line, expansion);
			was_expanded = 1;
		}
		break;
	}
	if (was_expanded)
	{
		free(data->get_line);
		data->get_line = string_repetitions(line);
	}
}

int new_buffer(char *buffer, char *str_to_add)
{
	int length, i;

	length = string_size(buffer);
	for (i = 0; str_to_add[i]; i++)
	{
		buffer[length + i] = str_to_add[i];
	}
	buffer[length + i] = '\0';
	return (length + i);
}