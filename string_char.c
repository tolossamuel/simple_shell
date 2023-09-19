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
	char *result;
	int num1 = 0, num2 = 0;

	if (string_one == NULL)
		string_one = "";
	num1 = string_size(string_one);
	if (string_two == NULL)
		string_two = "";
	num2 = string_size(string_two);
	result = malloc(sizeof(char) * (num1 + num2 + 1));
	if (result == NULL)
	{
		errno = ENOMEM;
		perror("ERROR");
		return (NULL);
	}

	for (num1 = 0; string_one[num1] != '\0'; num1++)
		result[num1] = string_one[num1];
	free(string_one);
	for (num2 = 0; string_two[num2] != '\0'; num2++)
	{
		result[num1] = string_two[num2];
		num1++;
	}
	result[num1] = '\0';
	return (result);
}

/**
 * string_repetitions - duplicates a string
 * @string: a pointer to a null-terminated character array (string)
 * Return: duplicated copy of the input string
*/
char *string_repetitions(char *string)
{
	char *result;
	int length, num1;

	if (string == NULL)
		return (NULL);

	length = string_size(string) + 1;

	result = malloc(sizeof(char) * length);

	if (result == NULL)
	{
		errno = ENOMEM;
		perror("ERROR");
		return (NULL);
	}
	for (num1 = 0; num1 < length ; num1++)
	{
		result[num1] = string[num1];
	}

	return (result);
}
