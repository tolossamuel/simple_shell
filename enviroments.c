#include "shell.h"

int env_builders(about *info)
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


int unset_key(about *info)
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


int builder_set_key(about *info)
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
