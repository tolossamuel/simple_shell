#include "shell.h"
#include <errno.h>

char **split_path(char *path)
{
	
	char *tokenize;
	char *cmd_path = string_repetitions(path);
	char **array;
	int i = 0;
	
	array = malloc(sizeof(char *) * (string_size(path))/2);

	tokenize = strtok(cmd_path, ":");
	while (tokenize)
	{
		*array = malloc(sizeof(char) * string_size(tokenize));
		array[i] = tokenize;
		tokenize = strtok(NULL, ":");
		i++;
	}
	array[i] = NULL;

	return (array);
}

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