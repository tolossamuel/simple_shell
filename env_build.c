#include "shell.h"

int env_builders(data_of_program *data)
{
	int num1;
	char cmd_name[50] = {'\0'};
	char *var_copy = NULL;
	if (data->tokens[1] == NULL)
		env_print(data);
	else
	{
		for (num1 = 0; data->tokens[1][num1]; num1++)
		{
			if (data->tokens[1][num1] == '=')
			{
				var_copy = string_repetitions(get_key(cmd_name, data));
				if (var_copy != NULL)
					set_key(cmd_name, data->tokens[1] + num1 + 1, data);

				
				env_print(data);
				if (get_key(cmd_name, data) == NULL)
				{
					_print(data->tokens[1]);
					_print("\n");
				}
				else
				{
					set_key(cmd_name, var_copy, data);
					free(var_copy);
				}
				return (0);
			}
			cmd_name[num1] = data->tokens[1][num1];
		}
		errno = 2;
		perror(data->cmd_name);
		errno = 127;
	}
	return (0);
}

int builder_set_key(data_of_program *data)
{
	if (data->tokens[1] == NULL || data->tokens[2] == NULL)
		return (0);
	if (data->tokens[3] != NULL)
	{
		errno = E2BIG;
		perror(data->cmd_name);
		return (5);
	}

	set_key(data->tokens[1], data->tokens[2], data);

	return (0);
}


int unset_key(data_of_program *data)
{
	if (data->tokens[1] == NULL)
		return (0);
	if (data->tokens[2] != NULL)
	{
		errno = E2BIG;
		perror(data->cmd_name);
		return (5);
	}
	remove_key(data->tokens[1], data);

	return (0);
}
