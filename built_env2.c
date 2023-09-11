#include "shell.h"
#include "main.h"

int builtins_list(data_of_program *data)
{
	
	build_structure menu_list[] = {
		{"exit", exit_env},
		{"unsetenv", unset_key},
		{"cd", command_built},
		{"alias", builtin_alias},
		{"env", env_builders},
		{"help", help_builtin},
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