#include "shell.h"

/**
 * free_data - Free allocated memory and set pointers to
 * NULL in the about struct.
 * @info: a pointer to a program_info structure, likely containing
 * program-related information and environment variables.
 * Return: It doesn't return any value (void function)
*/
void free_data(about_info *info)
{
	if (info->tokens)
		free_array_pointes(info->tokens);
	if (info->get_line)
		free(info->get_line);
	if (info->cmd_name)
		free(info->cmd_name);
	info->get_line = NULL;
	info->cmd_name = NULL;
	info->tokens = NULL;
}

/**
 * free_all - Free allocated memory and close a file descriptor,
 * if applicable, in the `about` struct.
 * @info: a pointer to a program_info structure, likely containing
 * program-related information and environment variables.
 * Return: It doesn't return any value (void function)
*/
void free_all(about_info *info)
{
	if (info->file_desc != 0)
	{
		if (close(info->file_desc))
			perror(info->name_projects);
	}
	free_data(info);
	free_array_pointes(info->env);
	free_array_pointes(info->alias_list);
}

/**
 * free_array_pointes - Free memory allocated for an array of
 * pointers and set the array to NULL.
 * @array: a pointer to an array of pointers
 * Return: It doesn't return any value (void function)
*/
void free_array_pointes(char **array)
{
	int num1;

	if (array != NULL)
	{
		for (num1 = 0; array[num1]; num1++)
			free(array[num1]);
		free(array);
		array = NULL;
	}
}
