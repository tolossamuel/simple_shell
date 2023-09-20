#include "shell.h"

/**
 * file_path - searches for an environment variable named
 * @name: const char for the functions
 * Return: NULL if not name else its value of char in functions
*/
char *file_path(const char *name)
{
	int num1, num2;
	char *value;

	if (!name)
		return (NULL);
	for (num1 = 0; environ[num1]; num1++)
	{
		num2 = 0;
		if (name[num2] == environ[num1][num2])
		{
			while (name[num2])
			{
				if (name[num2] != environ[num1][num2])
					break;

				num2++;
			}
			if (name[num2] == '\0')
			{
				value = (environ[num1] + num2 + 1);
				return (value);
			}
		}
	}
	return (NULL);
}

/**
 * search_file_path - attempts to find the full path of a file
 * named filename within the directories specified in the arr array
 * @filename: the name of the file to search for in the directories
 * specified in arr
 * @arr: an array of strings that represents a list of directories
 * Return: the full path of a file if found, or NULL if the file
 * is not found in the specified directories
*/
char *search_file_path(char *filename, char **arr)
{

	char *string;
	int num1 = 0;
	struct stat structure;

	while (arr[num1])
	{
		string = string_repetitions(arr[num1]);
		string = string_merging(string, "/");
		string = string_merging(string, filename);
		if (stat(string, &structure) == 0)
		{
			return (string);
		}
		free(string);
		num1++;
	}
	return (NULL);
}
