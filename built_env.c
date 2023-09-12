#include "shell.h"

int exit_env(program_info *info)
{
	int num1;

	if (info->tokens[1] != NULL)
	{
		for (num1 = 0; info->tokens[1][num1]; num1++)
			if ((info->tokens[1][num1] < '0' || info->tokens[1][num1] > '9')
				&& info->tokens[1][num1] != '+')
			{
				errno = 2;
				return (2);
			}
		errno = _atoi(info->tokens[1]);
	}
	
	if (info != NULL) {
		free_all(info);
	}
	exit(errno);
}




int set_dir(program_info *info, char *new_dir)
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
		set_key("PWD", new_dir, info);
	}
	set_key("OLDPW", old_dir, info);
	return (0);
}


int builtin_alias(program_info *info)
{
	int num1 = 0;
	if (info->tokens[1] == NULL)
		return (printf_fun(info, NULL));

	while (info->tokens[++num1])
	{
		if (size_characters(info->tokens[num1], "="))
			set_fun(info->tokens[num1], info);
		else
			printf_fun(info, info->tokens[num1]);
	}

	return (0);
}