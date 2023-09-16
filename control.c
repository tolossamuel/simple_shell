#include "shell.h"

/**
 * get_fun - Retrieve the value of a specified alias
 * @info: a pointer to a structure likely holding
 * program-related information
 * @name: a string representing the alias name
 * Return: the value of an alias if it exists otherwise NULL
*/
char *get_fun(about_info *info, char *name)
{
	int num1, alias_length;

	if (name == NULL || info->alias_list == NULL)
		return (NULL);
	alias_length = string_size(name);
	for (num1 = 0; info->alias_list[num1]; num1++)
	{
		if (string_comparions(name, info->alias_list[num1], alias_length) &&
			info->alias_list[num1][alias_length] == '=')
		{
			return (info->alias_list[num1] + alias_length + 1);
		}
	}
	return (NULL);
}

/**
 * printf_fun - Print alias definitions based on a provided alias name
 * or print all aliases if name is NULL
 * @info: a pointer to a structure likely holding
 * program-related information
 * @name: a string representing the alias name
 * Return: an integer value, which is always 0 in this implementation.
 */
int printf_fun(about_info *info, char *name)
{
	int num1;
	int num2;
	int alias_length;
	char buffer[250] = {'\0'};

	if (info->alias_list)
	{
		alias_length = string_size(name);
		for (num1 = 0; info->alias_list[num1]; num1++)
		{
			if (!name || (string_comparions(info->alias_list[num1], name, alias_length)
				&&	info->alias_list[num1][alias_length] == '='))
			{
				for (num2 = 0; info->alias_list[num1][num2]; num2++)
				{
					buffer[num2] = info->alias_list[num1][num2];
					if (info->alias_list[num1][num2] == '=')
						break;
				}
				buffer[num2 + 1] = '\0';
				new_buffer(buffer, "'");
				new_buffer(buffer, info->alias_list[num1] + num2 + 1);
				new_buffer(buffer, "'\n");
				_print(buffer);
			}
		}
	}
	return (0);
}

/**
 * set_fun - Set an alias based on the provided alias string
 * @alias_string: a string representing an alias definition
 * @info: a pointer to a structure likely holding
 * program-related information
 * Return: It returns an integer result, which is 0 on success
 * or 1 if the alias_string or alias_list is not available
*/
int set_fun(char *alias_string, about_info *info)
{
	int num1;
	int num2;
	char buffer[250] = {'0'}, *temp = NULL;

	if (alias_string == NULL ||  info->alias_list == NULL)
		return (1);
	for (num1 = 0; alias_string[num1]; num1++)
		if (alias_string[num1] != '=')
			buffer[num1] = alias_string[num1];
		else
		{
			temp = get_fun(info, alias_string + num1 + 1);
			break;
		}
	for (num2 = 0; info->alias_list[num2]; num2++)
		if (string_comparions(buffer, info->alias_list[num2], num1) &&
			info->alias_list[num2][num1] == '=')
		{
			free(info->alias_list[num2]);
			break;
		}

	if (temp)
	{
		new_buffer(buffer, "=");
		new_buffer(buffer, temp);
		info->alias_list[num2] = string_repetitions(buffer);
	}
	else
		info->alias_list[num2] = string_repetitions(alias_string);
	return (0);
}
