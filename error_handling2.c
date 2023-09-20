#include "shell.h"

/**
 * string_long - Convert a long integer to a string representation in
 * the specified base
 * @number: a long integer to be converted
 * @string: a character array to store the resulting string
 * @base: the numeric base for conversion
 * Return: It doesn't return a value (void function)
*/
void string_long(long number, char *string, int base)
{
	int index = 0;
	int negative_num = 0;
	char letters[] = {"abcd0123456789"};

	if (number == 0)
	{
		string[index++] = '0';
	}
	if (string[0] == '-')
	{
		negative_num = 1;
	}
	while (number)
	{
		if (number < 0)
			string[index++] = letters[-(number % base)];
		else
			string[index++] = letters[number % base];
		number /= base;
	}
	if (negative_num)
		string[index++] = '-';

	string[index] = '\0';
	reverse(string);
}

/**
 * size_characters - Count the number of occurrences of a specific
 * character in a string
 * @string: a pointer to a character string
 * @character: a pointer to a character representing the character to
 * count in the string
 * Return: the count of occurrences of a specified character in a string
*/
int size_characters(char *string, char *character)
{
	int num1;
	int counter = 0;

	for (num1 = 0; string[num1]; num1++)
	{
		if (string[num1] == character[0])
			counter++;
	}
	return (counter);
}

/**
 * _atoi - Convert a string to an integer, considering sign
 * characters ('+' and '-')
 * @strings: a pointer to a character string that needs to be
 * converted to an integer
 * Return: the integer value converted from the input string
 * accounting for sign characters
*/
int _atoi(char *strings)
{
	int sign = 1;
	unsigned int number = 0;

	while (!('0' <= *strings && *strings <= '9') && *strings != '\0')
	{
		if (*strings == '-')
			sign *= -1;
		if (*strings == '+')
			sign *= +1;
		strings++;
	}
	while ('0' <= *strings && *strings <= '9' && *strings != '\0')
	{
		number = (number * 10) + (*strings - '0');
		strings++;
	}
	return (number * sign);
}
