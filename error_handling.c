#include "shell.h"


/**
 * free_all - Free allocated memory and close a file descriptor,
 * if applicable, in the `about` struct.
 * @info: a pointer to a program_info structure, likely containing
 * program-related information and environment variables.
 * Return: It doesn't return any value (void function)
*/
void free_all(about_info *info)
{
	if (info->tokens != NULL)
		free(info->tokens);
	if (info->get_line != NULL)
		free(info->get_line);
	if (info->cmd_name != NULL)
		free(info->cmd_name);
	info->get_line = NULL;
	info->cmd_name = NULL;
	info->tokens = NULL;
	if (info->env)
	{
		free(info->env);
		info->env = NULL;
	}
	if (info->alias_list)
	{
		free(info->alias_list);
		info->alias_list = NULL;
	}
}
