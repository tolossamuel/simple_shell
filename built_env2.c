#include "shell.h"

int built_list(data_of_program *data)
{
	
	build_structure menu_list[] = {
		{"exit", exit_env},
		{"unsetenv", unset_key},
		{"cd", command_built},
		{"alias", builtin_alias},
		{"env", env_builders},
		{"help", help_built},
		{"setenv", builder_set_key},
		{NULL, NULL}
	};
	int nums;

	for (nums = 0; menu_list[nums].built_in != NULL; nums++)
	{
		if (string_comparions(menu_list[nums].built_in, data->cmd_name, 0))
		{

			return (menu_list[nums].function(data));
		}
	}
	return (-1);
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

int help_built(data_of_program *data)
{
	int num1;
	int length = 0;
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

	for (num1 = 0; messages[num1]; num1++)
	{
		length = string_size(data->tokens[1]);
		if (string_comparions(data->tokens[1], messages[num1], length))
		{
			_print(messages[num1] + length + 1);
			return (1);
		}
	}
	errno = EINVAL;
	perror(data->cmd_name);
	return (0);
}
