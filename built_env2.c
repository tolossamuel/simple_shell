#include "shell.h"

/**
 * built_list - Execute the specified built-in command from a predefined list
 * @info: a pointer to a structure likely holding program-related information
 * Return: he result of executing the specified command or
 * -1 if the command is not found
 */
int built_list(about_info *info)
{
	env_structure menu_list[] = {
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
		if (string_comparions(menu_list[nums].built_in, info->cmd_name, 0))
		{
			return (menu_list[nums].function(info));
		}
	}
	return (-1);
}

/**
 * command_built - Change the current directory based on the provided
 * argument or switch to the previous directory
 * @info: pointer to a structure likely holding program-related information
 * Return: an integer result indicating the success or failure of changing
 * the current directory
 */
int command_built(about_info *info)
{
	char *dir_home = get_key("HOME", info), *dir_old = NULL;
	char old_dir[128] = {0};
	int error_code = 0;

	if (info->tokens[1])
	{
		if (string_comparions(info->tokens[1], "-", 0))
		{
			dir_old = get_key("OLDPWD", info);
			if (dir_old)
				error_code = set_dir(info, dir_old);
			_print(get_key("PWD", info));
			_print("\n");
			return (error_code);
		}
		else
		{
			return (set_dir(info, info->tokens[1]));
		}
	}
	else
	{
		if (!dir_home)
			dir_home = getcwd(old_dir, 128);

		return (set_dir(info, dir_home));
	}
	return (0);
}
/**
 * help_built - Display help messages for built-in commands or provide
 * an error message if the command is not found
 * @info: pointer to a structure likely holding program-related information
 * Return: It returns a success or error code based on whether it successfully
 * displays help messages or provides an error message
*/
int help_built(about_info *info)
{
	int num1;
	int length = 0;
	char *messages[6] = {NULL};

	messages[0] = HELP_MSG;
	if (info->tokens[1] == NULL)
	{
		_print(messages[0] + 6);
		return (1);
	}
	if (info->tokens[2] != NULL)
	{
		errno = E2BIG;
		perror(info->cmd_name);
		return (5);
	}
	messages[1] = HELP_EXIT_MSG;
	messages[2] = HELP_ENV_MSG;
	messages[3] = HELP_SETENV_MSG;
	messages[4] = HELP_UNSETENV_MSG;
	messages[5] = HELP_CD_MSG;
	for (num1 = 0; messages[num1]; num1++)
	{
		length = string_size(info->tokens[1]);
		if (string_comparions(info->tokens[1], messages[num1], length))
		{
			_print(messages[num1] + length + 1);
			return (1);
		}
	}
	errno = EINVAL;
	perror(info->cmd_name);
	return (0);
}
