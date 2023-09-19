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
	int counter = 0;

	if (string == NULL)
		return (0);
	while (string[counter++] != '\0')
	{
	}
	return (counter - 1);
}

/**
 * getline_fun - reads a line from a file stream, dynamically
 * resizing the buffer as needed
 * @ptr_lin: A pointer to a pointer to a character buffer where
 * the line read from the file will be stored
 * @num: A pointer to a size_t variable representing the size
 * of the buffer pointed
 * @stream: A FILE pointer representing the input stream from
 * which the line is read
 * Return:  the number of characters read from the file stream
 * or -1 if an error occurs
 */
ssize_t getline_fun(char **ptr_lin, size_t *num, FILE *stream)
{
	size_t store = *num;
	size_t num1 = 0;
	int num2;
	char *temp;

	if (*ptr_lin == NULL)
	{
		*ptr_lin = (char *)malloc(store);
		if (*ptr_lin == NULL)
		{
			return (-1);
		}
	}
	while ((num2 = fgetc(stream)) != EOF)
	{
		if (num1 >= store - 1)
		{
			store *= 2;
			temp = (char *)realloc(*ptr_lin, store);
			if (temp == NULL)
			{
				return (-1);
			}
			*ptr_lin = temp;
			*num = store;
		}
		(*ptr_lin)[num1++] = (char)num2;
		if (num2 == '\n')
		{
			break;
		}
	}

	if (num1 == 0 && num2 == EOF)
	{
		return (-1);
	}
	(*ptr_lin)[num1] = '\0';
	return (num1);
}
