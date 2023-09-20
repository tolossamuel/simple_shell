#include "shell.h"

/**
 * handle_error - Print error messages based on the given error code
 * and program information
 * @error_code:  an integer representing the error code
 * @info: a pointer to a program_info struct which contains program information
 * Return: zero (0)
*/
int handle_error(int error_code, about_info *info)
{
	char arr_string[10] = {'\0'};

	string_long((long) info->execute_counter, arr_string, 10);
	if (error_code == 2 || error_code == 3)
	{
		_printe(info->name_projects);
		_printe(": ");
		_printe(arr_string);
		_printe(": ");
		_printe(info->tokens[0]);
		if (error_code == 2)
			_printe(": ERROR (unexpected number): ");
		else
			_printe(": ERROR (can not redirect): ");
		_printe(info->tokens[1]);
		_printe("\n");
	}
	else if (error_code == 127)
	{
		_printe(info->name_projects);
		_printe(": ");
		_printe(arr_string);
		_printe(": ");
		_printe(info->cmd_name);
		_printe(": ERROR (not found)\n");
	}
	else if (error_code == 126)
	{
		_printe(info->name_projects);
		_printe(": ");
		_printe(arr_string);
		_printe(": ");
		_printe(info->cmd_name);
		_printe(": ERROR (no permission)\n");
	}
	return (0);
}

/**
 * _printe - Print a string to the standard error stream
 * @string: a pointer to a character string that needs to be printed
 * Return: the number of characters written to the respective output stream
*/
int _printe(char *string)
{
	return (write(STDERR_FILENO, string, string_size(string)));
}
/**
 * _print - Print a string to the standard output stream
 * @string: a pointer to a character string that needs to be printed
 * Return: the number of characters written to the respective output stream
 */
int _print(char *string)
{
	return (write(STDOUT_FILENO, string, string_size(string)));
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
