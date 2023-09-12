#include "shell.h"

void var_expand(program_info *info)
{
	int num1, num2;
	char line[BUFFER_SIZE] = {0}, expansion[BUFFER_SIZE] = {'\0'}, *temp;

	if (info->get_line == NULL)
		return;
	new_buffer(line, info->get_line);
	for (num1 = 0; line[num1]; num1++)
		if (line[num1] == '#')
			line[num1--] = '\0';
		else if (line[num1] == '$' && line[num1 + 1] == '?')
		{
			line[num1] = '\0';
			string_long(errno, expansion, 10);
			new_buffer(line, expansion);
			new_buffer(line, info->get_line + num1 + 2);
		}
		else if (line[num1] == '$' && line[num1 + 1] == '$')
		{
			line[num1] = '\0';
			string_long(getpid(), expansion, 10);
			new_buffer(line, expansion);
			new_buffer(line, info->get_line + num1 + 2);
		}
		else if (line[num1] == '$' && (line[num1 + 1] == ' ' || line[num1 + 1] == '\0'))
			continue;
		else if (line[num1] == '$')
		{
			for (num2 = 1; line[num1 + num2] && line[num1 + num2] != ' '; num2++)
				expansion[num2 - 1] = line[num1 + num2];
			temp = get_key(expansion, info);
			line[num1] = '\0', expansion[0] = '\0';
			new_buffer(expansion, line + num1 + num2);
			temp ? new_buffer(line, temp) : 1;
			new_buffer(line, expansion);
		}
	if (!string_comparions(info->get_line, line, 0))
	{
		free(info->get_line);
		info->get_line = string_repetitions(line);
	}
}

void expand_alias(program_info *info)
{
	int i, j, was_expanded = 0;
	char line[BUFFER_SIZE] = {0}, expansion[BUFFER_SIZE] = {'\0'}, *temp;

	if (info->get_line == NULL)
		return;

	new_buffer(line, info->get_line);

	for (i = 0; line[i]; i++)
	{
		for (j = 0; line[i + j] && line[i + j] != ' '; j++)
			expansion[j] = line[i + j];
		expansion[j] = '\0';

		temp = get_fun(info, expansion);
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
		free(info->get_line);
		info->get_line = string_repetitions(line);
	}
}

int new_buffer(char *buffer, char *concatenate_string)
{
	int length, i;

	length = string_size(buffer);
	for (i = 0; concatenate_string[i]; i++)
	{
		buffer[length + i] = concatenate_string[i];
	}
	buffer[length + i] = '\0';
	return (length + i);
}