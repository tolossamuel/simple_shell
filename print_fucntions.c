#include "shell.h"

/**
 * print_fun - Print a string to the standard output stream
 * @string: a pointer to a character string that needs to be printed
 * Return: the number of characters written to the respective output stream
 */
int print_fun(char *string)
{
	return (write(STDERR_FILENO, string, string_size(string)));
}

/**
 * string_size - Calculates the length of the input string
 * @string: a pointer to a character array (a string) whose
 * length needs to be determined
 * Return: the length of the input string excluding the null
 * terminator or 0 if the string is NULL
 */
int string_size(char *string)
{
	int i = 0;

	if (!string)
		return (0);

	while (*string++)
		i++;
	return (i);
}
