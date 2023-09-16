#include "shell.h"

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
 * string_comparions - compares two strings up to a specified number
 * of characters
 * @string_one: the first input string to be compared
 * @string_two: the second input string to be compared
 * @number: number of characters to compare in the strings
 * Return: 1 if the two input strings are equal up to the specified
 * number of characters, 0 otherwise,
*/
int string_comparions(char *string_one, char *string_two, int number)
{
	int loops;

	if (string_two == NULL && string_one == NULL)
	{
		return (1);
	}
	if (string_one == NULL || string_two == NULL)
	{
		return (0);
	}
	if (number == 0)
	{
		if (string_size(string_one) != string_size(string_two))
			return (0);
		for (loops = 0; string_one[loops]; loops++)
		{
			if (string_one[loops] != string_two[loops])
				return (0);
		}
		return (1);
	}
	else
	{
		for (loops = 0; loops < number ; loops++)
		{
			if (string_one[loops] != string_two[loops])
			return (0);
		}
		return (1);
	}
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
 * reverse - a function reverses the characters in a given string
 * @string: a character array (string)
 * Return:  function does not return a value
*/
void reverse(char *string)
{

	int num1 = 0, length = string_size(string) - 1;
	char hold;

	while (num1 < length)
	{
		hold = string[num1];
		string[num1++] = string[length];
		string[length--] = hold;
	}
}
