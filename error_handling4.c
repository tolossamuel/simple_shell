#include "shell.h"

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

int string_comparions(char *string1, char *string2, int number)
{
	int loops;

	if (string2 == NULL && string1 == NULL)
		return (1);

	if (string1 == NULL || string2 == NULL)
		return (0);

	if (number == 0)
	{
		if (string_size(string1) != string_size(string2))
			return (0);
		for (loops = 0; string1[loops]; loops++)
		{
			if (string1[loops] != string2[loops])
				return (0);
		}
		return (1);
	}
	else
	{
		for (loops = 0; loops < number ; loops++)
		{
			if (string1[loops] != string2[loops])
			return (0);
		}
		return (1);
	}
}

char *string_merging(char *string1, char *string2)
{
	char *result;
	int num1 = 0, num2 = 0;

	if (string1 == NULL)
		string1 = "";
	num1 = string_size(string1);

	if (string2 == NULL)
		string2 = "";
	num2 = string_size(string2);

	result = malloc(sizeof(char) * (num1 + num2 + 1));
	if (result == NULL)
	{
		errno = ENOMEM;
		perror("ERROR");
		return (NULL);
	}

	for (num1 = 0; string1[num1] != '\0'; num1++)
		result[num1] = string1[num1];
	free(string1);

	for (num2 = 0; string2[num2] != '\0'; num2++)
	{
		result[num1] = string2[num2];
		num1++;
	}

	result[num1] = '\0';
	return (result);
}


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
