#include "shell.h"

void string_long(long number, char *string, int base)
{
	int index = 0;
	int negative_num = 0;
	char letters[] = {"0123456789abcdef"};

	if (number == 0)
		string[index++] = '0';

	if (string[0] == '-')
		negative_num = 1;

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




int size_characters(char *string, char *character)
{
	int num1 = 0;
	int counter = 0;

	for (; string[num1]; num1++)
	{
		if (string[num1] == character[0])
			counter++;
	}
	return (counter);
}
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
