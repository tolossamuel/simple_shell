#include "shell.h"

int exit_env(data_of_program *data)
{
	int i;

	if (data->tokens[1] != NULL)
	{
		for (i = 0; data->tokens[1][i]; i++)
			if ((data->tokens[1][i] < '0' || data->tokens[1][i] > '9')
				&& data->tokens[1][i] != '+')
			{
				errno = 2;
				return (2);
			}
		errno = _atoi(data->tokens[1]);
	}
	free_all(data);
	exit(errno);
}

int command_built(data_of_program *data)
{
	char *dir_home = get_key("HOME", data), *dir_old = NULL;
	char old_dir[128] = {0};
	int error_code = 0;

	if (data->tokens[1])
	{
		if (string_comparions(data->tokens[1], "-", 0))
		{
			dir_old = get_key("OLDPWD", data);
			if (dir_old)
				error_code = set_dir(data, dir_old);
			_print(get_key("PWD", data));
			_print("\n");

			return (error_code);
		}
		else
		{
			return (set_dir(data, data->tokens[1]));
		}
	}
	else
	{
		if (!dir_home)
			dir_home = getcwd(old_dir, 128);

		return (set_dir(data, dir_home));
	}
	return (0);
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
	set_key("OLDPWD", old_dir, data);
	return (0);
}

int help_builtin(data_of_program *data)
{
	int i, length = 0;
	char *messages[6] = {NULL};

	messages[0] = HELP_MSG;

	/* validate args */
	if (data->tokens[1] == NULL)
	{
		_print(messages[0] + 6);
		return (1);
	}
	if (data->tokens[2] != NULL)
	{
		errno = E2BIG;
		perror(data->cmd_name);
		return (5);
	}
	messages[1] = HELP_EXIT_MSG;
	messages[2] = HELP_ENV_MSG;
	messages[3] = HELP_SETENV_MSG;
	messages[4] = HELP_UNSETENV_MSG;
	messages[5] = HELP_CD_MSG;

	for (i = 0; messages[i]; i++)
	{
		length = string_size(data->tokens[1]);
		if (string_comparions(data->tokens[1], messages[i], length))
		{
			_print(messages[i] + length + 1);
			return (1);
		}
	}
	/*if there is no match, print error and return -1 */
	errno = EINVAL;
	perror(data->cmd_name);
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