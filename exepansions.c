#include "shell.h"

/**
 * var_expand - processes and expands variables in a given text line
 * stored in the "info" structure
 * @info: a struct of type "about_info" in the function "var_expand
 * Return: does not have a return value (void)
*/
void var_expand(about_info *info)
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
		} else if (line[num1] == '$' && line[num1 + 1] == '$')
		{
			line[num1] = '\0';
			string_long(getpid(), expansion, 10);
			new_buffer(line, expansion);
			new_buffer(line, info->get_line + num1 + 2);
		} else if (line[num1] == '$' && (line[num1 + 1] == ' '
		|| line[num1 + 1] == '\0'))
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

/**
 * expand_alias - searches for and expands aliases in the provided
 * input line stored in "info->get_line"
 * @info: a struct of type "about_info" in the function "var_expand
 * Return: does not have a return value (void)
*/
void expand_alias(about_info *info)
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

/**
 * new_buffer - The "new_buffer" function appends the "concatenate_string"
 * to the end of the "buffer"
 * @buffer: a character array to which "concatenate_string" is appended
 * @concatenate_string: a string that is concatenated to "buffer"
 * Return: the total length of the resulting string after appending
 * "concatenate_string" to "buffer"
*/
int new_buffer(char *buffer, char *concatenate_string)
{
	int num1, num2;

	num1 = string_size(buffer);
	for (num2 = 0; concatenate_string[num2]; num2++)
	{
		buffer[num1 + num2] = concatenate_string[num2];
	}
	buffer[num1 + num2] = '\0';
	return (num1 + num2);
}
