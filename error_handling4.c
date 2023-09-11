#include "shell.h"

int string_size(char *string)
{
	int length = 0;

	if (string == NULL)
		return (0);

	while (string[length++] != '\0')
	{
	}
	return (--length);
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
		perror("Error");
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
	int iterator;

	if (string1 == NULL && string2 == NULL)
		return (1);

	if (string1 == NULL || string2 == NULL)
		return (0);

	if (number == 0)
	{
		if (string_size(string1) != string_size(string2))
			return (0);
		for (iterator = 0; string1[iterator]; iterator++)
		{
			if (string1[iterator] != string2[iterator])
				return (0);
		}
		return (1);
	}
	else
	{
		for (iterator = 0; iterator < number ; iterator++)
		{
			if (string1[iterator] != string2[iterator])
			return (0);
		}
		return (1);
	}
}

char *string_merging(char *string1, char *string2)
{
	char *result;
	int length1 = 0, length2 = 0;

	if (string1 == NULL)
		string1 = "";
	length1 = string_size(string1);

	if (string2 == NULL)
		string2 = "";
	length2 = string_size(string2);

	result = malloc(sizeof(char) * (length1 + length2 + 1));
	if (result == NULL)
	{
		errno = ENOMEM;
		perror("ERROR");
		return (NULL);
	}

	for (length1 = 0; string1[length1] != '\0'; length1++)
		result[length1] = string1[length1];
	free(string1);

	for (length2 = 0; string2[length2] != '\0'; length2++)
	{
		result[length1] = string2[length2];
		length1++;
	}

	result[length1] = '\0';
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
