#include "shell.h"

/**
 * env_builders - it Handle environment variable commands, including setting
 * printing, and error handling
 * @info: a pointer to a program_info structure, likely containing
 * program-related information and environment variables
 * Return: an integer result, which is always 0 in this implementation
 */
int env_builders(about_info *info)
{
	int num1;
	char *var_copy = NULL;
	char cmd_name[50] = {'\0'};

	if (info->tokens[1] == NULL)
		env_print(info);
	else
	{
		for (num1 = 0; info->tokens[1][num1]; num1++)
		{
			if (info->tokens[1][num1] == '=')
			{
				var_copy = string_repetitions(get_key(cmd_name, info));
				if (var_copy != NULL)
					set_key(cmd_name, info->tokens[1] + num1 + 1, info);
				env_print(info);
				if (get_key(cmd_name, info) == NULL)
				{
					_print(info->tokens[1]);
					_print("\n");
				}
				else
				{
					set_key(cmd_name, var_copy, info);
					free(var_copy);
				}
				return (0);
			}
			cmd_name[num1] = info->tokens[1][num1];
		}
		errno = 2;
		perror(info->cmd_name);
		errno = 127;
	}
	return (0);
}

/**
 * unset_key - Unset (remove) an environment variable based on the provided key
 * @info: a pointer to a program_info structure likely containing
 * program-related information and environment variables
 * Return: 0 on success or 5 if the number of arguments is incorrect
*/
int unset_key(about_info *info)
{
	if (info->tokens[1] == NULL)
		return (0);
	if (info->tokens[2] != NULL)
	{
		errno = E2BIG;
		perror(info->cmd_name);
		return (5);
	}
	remove_key(info->tokens[1], info);
	return (0);
}

/**
 * builder_set_key - Set an environment variable based on the provided key
 * and value
 * @info: a pointer to a program_info structure likely containing
 * program-related information and environment variables
 * Return: 0 on success or 5 if the number of arguments is incorrect
*/
int builder_set_key(about_info *info)
{
	if (info->tokens[1] == NULL || info->tokens[2] == NULL)
		return (0);
	if (info->tokens[3] != NULL)
	{
		errno = E2BIG;
		perror(info->cmd_name);
		return (5);
	}
	set_key(info->tokens[1], info->tokens[2], info);
	return (0);
}
