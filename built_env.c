#include "shell.h"

int exit_env(data_of_program *data)
{
	int num1;

	if (data->tokens[1] != NULL)
	{
		for (num1 = 0; data->tokens[1][num1]; num1++)
			if ((data->tokens[1][num1] < '0' || data->tokens[1][num1] > '9')
				&& data->tokens[1][num1] != '+')
			{
				errno = 2;
				return (2);
			}
		errno = _atoi(data->tokens[1]);
	}
	
	if (data != NULL) {
		free_all(data);
	}
	exit(errno);
}




int set_dir(data_of_program *data, char *new_dir)
{
	char old_dir[128] = {0};
	int err_code = 0;

	getcwd(old_dir, 128);

	if (!string_comparions(old_dir, new_dir, 0))
	{
		err_code = chdir(new_dir);
		if (err_code == -1)
		{
			errno = 2;
			return (3);
		}
		set_key("PWD", new_dir, data);
	}
	set_key("OLDPW", old_dir, data);
	return (0);
}


int builtin_alias(data_of_program *data)
{
	int i = 0;
	if (data->tokens[1] == NULL)
		return (printf_fun(data, NULL));

	while (data->tokens[++i])
	{
		if (size_characters(data->tokens[i], "="))
			set_fun(data->tokens[i], data);
		else
			printf_fun(data, data->tokens[i]);
	}

	return (0);
}