#include "shell.h"

void string_long(long number, char *string, int base)
{
	int index = 0, inNegative = 0;
	long var1 = number;
	char letters[] = {"0123456789abcdef"};

	if (var1 == 0)
		string[index++] = '0';

	if (string[0] == '-')
		inNegative = 1;

	while (var1)
	{
		if (var1 < 0)
			string[index++] = letters[-(var1 % base)];
		else
			string[index++] = letters[var1 % base];
		var1 /= base;
	}
	if (inNegative)
		string[index++] = '-';

	string[index] = '\0';
	string_reverse(string);
}


int _atoi(char *s)
{
	int sign = 1;
	unsigned int number = 0;
	while (!('0' <= *s && *s <= '9') && *s != '\0')
	{
		if (*s == '-')
			sign *= -1;
		if (*s == '+')
			sign *= +1;
		s++;
	}
	while ('0' <= *s && *s <= '9' && *s != '\0')
	{

		number = (number * 10) + (*s - '0');
		s++;
	}
	return (number * sign);
}

int size_characters(char *string, char *character)
{
	int i = 0, counter = 0;

	for (; string[i]; i++)
	{
		if (string[i] == character[0])
			counter++;
	}
	return (counter);
}
