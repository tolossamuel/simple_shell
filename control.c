#include "shell.h"

int printf_fun(data_of_program *data, char *alias)
{
	int num1;
	int num2;
	int alias_length;
	char buffer[250] = {'\0'};

	if (data->alias_list)
	{
		alias_length = string_size(alias);
		for (num1 = 0; data->alias_list[num1]; num1++)
		{
			if (!alias || (string_comparions(data->alias_list[num1], alias, alias_length)
				&&	data->alias_list[num1][alias_length] == '='))
			{
				for (num2 = 0; data->alias_list[num1][num2]; num2++)
				{
					buffer[num2] = data->alias_list[num1][num2];
					if (data->alias_list[num1][num2] == '=')
						break;
				}
				buffer[num2 + 1] = '\0';
				new_buffer(buffer, "'");
				new_buffer(buffer, data->alias_list[num1] + num2 + 1);
				new_buffer(buffer, "'\n");
				_print(buffer);
			}
		}
	}

	return (0);
}
char *get_fun(data_of_program *data, char *name)
{
	int num1, alias_length;
	if (name == NULL || data->alias_list == NULL)
		return (NULL);

	alias_length = string_size(name);

	for (num1 = 0; data->alias_list[num1]; num1++)
	{
		if (string_comparions(name, data->alias_list[num1], alias_length) &&
			data->alias_list[num1][alias_length] == '=')
		{
			return (data->alias_list[num1] + alias_length + 1);
		}
	}
	return (NULL);

}

int set_fun(char *alias_string, data_of_program *data)
{
	int num1;
	int num2;
	char buffer[250] = {'0'}, *temp = NULL;

	if (alias_string == NULL ||  data->alias_list == NULL)
		return (1);
	for (num1 = 0; alias_string[num1]; num1++)
		if (alias_string[num1] != '=')
			buffer[num1] = alias_string[num1];
		else
		{
			temp = get_fun(data, alias_string + num1 + 1);
			break;
		}
	for (num2 = 0; data->alias_list[num2]; num2++)
		if (string_comparions(buffer, data->alias_list[num2], num1) &&
			data->alias_list[num2][num1] == '=')
		{
			free(data->alias_list[num2]);
			break;
		}

	if (temp)
	{
		new_buffer(buffer, "=");
		new_buffer(buffer, temp);
		data->alias_list[num2] = string_repetitions(buffer);
	}
	else 
		data->alias_list[num2] = string_repetitions(alias_string);
	return (0);
}
