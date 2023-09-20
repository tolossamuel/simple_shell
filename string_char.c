#include "shell.h"
#include <errno.h>

/**
 * split_path - unction tokenize a colon-separated
 * string path into an array of strings, where each
 * element represents a path component
 * @path: a string containing colon-separated path
 * components to be split and stored in an array
 * Return: an array of strings, with each element
 * representing a path component extracted
*/
char **split_path(char *path)
{
	char *tokenize;
	char *cmd_path = string_repetitions(path);
	char **array;
	int num1 = 0;

	array = malloc(sizeof(char *) * (string_size(path)) / 2);
	tokenize = strtok(cmd_path, ":");
	while (tokenize)
	{
		*array = malloc(sizeof(char) * string_size(tokenize));
		array[num1] = tokenize;
		tokenize = strtok(NULL, ":");
		num1++;
	}
	array[num1] = NULL;
	return (array);
}

/**
 * string_merging - a function concatenates two strings
 * (string_one and string_two)
 * @string_one: character arrays representing two separate strings
 * @string_two: character arrays representing two separate strings
 * Return: the merged string obtained by concatenating string_one
 * and string_two
*/
char *string_merging(char *string_one, char *string_two)
{
	char *ret = string_one;

	while (*string_one)
		string_one++;
	while (*string_two)
		*string_one++ = *string_two++;
	*string_one = *string_two;
	return (ret);
}

/**
 * string_repetitions - duplicates a string
 * @string: a pointer to a null-terminated character array (string)
 * Return: duplicated copy of the input string
*/
char *string_repetitions(char *string)
{
	int length = 0;
	char *ret;

	if (string == NULL)
		return (NULL);
	while (*string++)
		length++;
	ret = malloc(sizeof(char) * (length + 1));
	if (!ret)
		return (NULL);
	for (length++; length--;)
		ret[length] = *--string;
	return (ret);
}
