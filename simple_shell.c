#include "shell.h"
#include <stdlib.h>
#include <stdio.h>

int main(int argc, char *argv[], char *env[])
{
	program_info stru_data = {NULL}, *info = &stru_data;
	char *prompt = "";

	start_with(info, argc, argv, env);
	signal(SIGINT, handle_short_cut);
	if (isatty(STDIN_FILENO) && isatty(STDOUT_FILENO) && argc == 1)
	{
		errno = 2;
		prompt = PROMPT_MSG;
	}
	errno = 0;
	size_of_(prompt, info);
	return (0);
}
void handle_short_cut(int operations UNUSED)
{
	_print("\n");
	_print(PROMPT_MSG);
}

void start_with(program_info *info, int argc, char *argv[], char **env)
{
	int num1 = 0;

	info->Name_projects = argv[0];
	info->get_line = NULL;
	info->cmd_name = NULL;
	info->execute_counter = 0;
	if (argc == 1)
		info->file_desc = STDIN_FILENO;
	else
	{
		info->file_desc = open(argv[1], O_RDONLY);
		if (info->file_desc == -1)
		{
			_printe(info->Name_projects);
			_printe(": 0: does not open ");
			_printe(argv[1]);
			_printe("\n");
			exit(127);
		}
	}
	info->tokens = NULL;
	info->env = malloc(sizeof(char *) * 50);
	if (env)
	{
		for (; env[num1]; num1++)
		{
			info->env[num1] = string_repetitions(env[num1]);
		}
	}
	info->env[num1] = NULL;
	env = info->env;

	info->alias_list = malloc(sizeof(char *) * 20);
	for (num1 = 0; num1 < 20; num1++)
	{
		info->alias_list[num1] = NULL;
	}
}

void size_of_(char *prompt, program_info *info)
{
	int error_code = 0, string_len = 0;

	while (++(info->execute_counter))
	{
		_print(prompt);
		error_code = string_len = _getline(info);

		if (error_code == EOF)
		{
			free_all(info);
			exit(errno); 
		}
		if (string_len >= 1)
		{
			expand_alias(info);
			var_expand(info);
			tokenize_data(info);
			if (info->tokens[0])
			{
				error_code = executed(info);
				if (error_code != 0)
					handle_error(error_code, info);
			}
			free_data(info);
		}
	}
}