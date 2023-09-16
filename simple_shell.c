#include "shell.h"
#include <stdlib.h>
#include <stdio.h>

/**
 * main - function initializes a program structure, sets
 * up signal handling, and determines whether to display
 * a prompt message based on the input and terminal conditions
 * @argc: represents the number of command-line arguments
 * @argv: is an array of pointers to the command-line arguments
 * @env: is an array of pointers to the environment variables
 * Return:  function in C typically returns an integer value
 * In this specific code, it always returns 0. This return value
 * indicates that the program has exited successfully, without
 * any errors
 */
int main(int argc, char *argv[], char *env[])
{
	about_info stru_data = {NULL}, *info = &stru_data;
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

/**
 * handle_short_cut - function in one line: It prints a newline
 * character and then prints the PROMPT_MSG as a command prompt
 * @UNUSED: is not used within the function; it is included in
 * the parameter list to indicate that the parameter is intentionally
 * not used to suppress any "unused parameter" warnings from the compiler
 * Return: function doesn't return a value
 */
void handle_short_cut(int operations UNUSED)
{
	_print("\n");
	_print(PROMPT_MSG);
}

/**
 * start_with - function initializes various fields and variables
 * in the about struct based on the input arguments argc, argv,
 * and env. In one line, it sets up the initial environment
 * for the shell program
 * @info: a pointer to a struct about that holds information about
 * the shell program's environment and configuration
 * @argc: represents the number of command-line arguments
 * @argv: is an array of pointers to the command-line arguments
 * @env: is an array of pointers to the environment variables
 * Return: the functions does not return any thing
 */
void start_with(about_info *info, int argc, char *argv[], char **env)
{
	int num1 = 0;

	info->name_projects = argv[0];
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
			_printe(info->name_projects);
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

/**
 * size_of_ - function continuously reads input lines, processes them
 * and executes commands in a shell-like environment with the
 * provided prompt
 * @prompt: a string containing the prompt message
 * @info: a pointer to a struct containing program information
 * Return: The functions does not return any thing
 */
void size_of_(char *prompt, about_info *info)
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
