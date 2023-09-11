#include "shell.h"
#include <stdlib.h>
#include <stdio.h>

int main(int argc, char *argv[], char *env[])
{
	data_of_program data_struct = {NULL}, *data = &data_struct;
	char *prompt = "";
	
	first_data(data, argc, argv, env);

	signal(SIGINT, handle_ctrl_c);

	if (isatty(STDIN_FILENO) && isatty(STDOUT_FILENO) && argc == 1)
	{
		errno = 2;
		prompt = PROMPT_MSG;
	}
	errno = 0;
	size_(prompt, data);
	return (0);
}
void handle_ctrl_c(int opr UNUSED)
{
	_print("\n");
	_print(PROMPT_MSG);
}

void first_data(data_of_program *data, int argc, char *argv[], char **env)
{
	int i = 0;

	data->Name_projects = argv[0];
	data->get_line = NULL;
	data->cmd_name = NULL;
	data->execute_counter = 0;
	/* define the file descriptor to be readed*/
	if (argc == 1)
		data->file_desc = STDIN_FILENO;
	else
	{
		data->file_desc = open(argv[1], O_RDONLY);
		if (data->file_desc == -1)
		{
			_printe(data->Name_projects);
			_printe(": 0: Can't open ");
			_printe(argv[1]);
			_printe("\n");
			exit(127);
		}
	}
	data->tokens = NULL;
	data->env = malloc(sizeof(char *) * 50);
	if (env)
	{
		for (; env[i]; i++)
		{
			data->env[i] = string_repetitions(env[i]);
		}
	}
	data->env[i] = NULL;
	env = data->env;

	data->alias_list = malloc(sizeof(char *) * 20);
	for (i = 0; i < 20; i++)
	{
		data->alias_list[i] = NULL;
	}
}

void size_(char *prompt, data_of_program *data)
{
	int error_code = 0, string_len = 0;

	while (++(data->execute_counter))
	{
		_print(prompt);
		error_code = string_len = _getline(data);

		if (error_code == EOF)
		{
			free_all(data);
			exit(errno); /* if EOF is the fisrt Char of string, exit*/
		}
		if (string_len >= 1)
		{
			expand_alias(data);
			var_expand(data);
			tokenize(data);
			if (data->tokens[0])
			{ /* if a text is given to prompt, execute */
				error_code = executed(data);
				if (error_code != 0)
					handle_error(error_code, data);
			}
			free_data(data);
		}
	}
}