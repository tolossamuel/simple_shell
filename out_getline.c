#include "shell.h"

/**
 * _getline - reads input data and processes it to prepare
 * commands for execution in a shell program
 * @info: a pointer to a "about" structure, which contains
 * information about the program's state and configuration
 * Return: the number of characters in the line read or
 * -1 if there's nothing more to read.
 */
int _getline(about_info *info)
{
	char buff[BUFFER_SIZE] = {'\0'};
	static char *array_commands[10] = {NULL};
	static char array_operators[10] = {'\0'};
	ssize_t bytes_read, i = 0;

	if (!array_commands[0] || (array_operators[0] == '&' && errno != 0) ||
		(array_operators[0] == '|' && errno == 0))
	{
		for (i = 0; array_commands[i]; i++)
		{
			free(array_commands[i]);
			array_commands[i] = NULL;
		}
		bytes_read = read(info->file_desc, &buff, BUFFER_SIZE - 1);
		if (bytes_read == 0)
			return (-1);

		i = 0;
		do {
			array_commands[i] = string_repetitions(str_tok(i ? NULL : buff, "\n;"));
			i = logical_operations(array_commands, i, array_operators);
		} while (array_commands[i++]);
	}
	info->get_line = array_commands[0];
	for (i = 0; array_commands[i]; i++)
	{
		array_commands[i] = array_commands[i + 1];
		array_operators[i] = array_operators[i + 1];
	}

	return (string_size(info->get_line));
}

/**
 * str_tok - function is a custom implementation of the strtok
 * function in C which tokenize a string based on a delimiter
 * @line: a pointer to the input string that is being tokenized
 * @delim: a pointer to a string containing delimiter characters
 * used to split the input string into tokens
 * Return: The next token in the input string or NULL
 * if there are no more tokens to be found.
 */
char *str_tok(char *line, char *delim)
{
	int num1;
	static char *str;
	char *copy_str;

	if (line != NULL)
		str = line;
	for (; *str != '\0'; str++)
	{
		for (num1 = 0; delim[num1] != '\0'; num1++)
		{
			if (*str == delim[num1])
			break;
		}
		if (delim[num1] == '\0')
			break;
	}
	copy_str = str;
	if (*copy_str == '\0')
		return (NULL);
	for (; *str != '\0'; str++)
	{
		for (num1 = 0; delim[num1] != '\0'; num1++)
		{
			if (*str == delim[num1])
			{
				*str = '\0';
				str++;
				return (copy_str);
			}
		}
	}
	return (copy_str);
}
