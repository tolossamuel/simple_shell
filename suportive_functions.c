#include "shell.h"

/**
 * supportive_func - supportive functions for betty style code
 * which functions contains more than 40 line of codes
 * @info: pointes for the functions
 * Return: nothings void functions
 */
void supportive_fun(about_info *info)
{
	if (info->get_line)
	{
		free(info->get_line);
	}
	info->get_line = NULL;
}

/**
 * supportive_free_fun - supportive functions for betty style code
 * which functions contains more than 40 line of codes
 * @directories: pointes for the functions
 * Return: nothings void functions
 */
void supportive_free_fun(char **directories)
{
	if (directories != NULL)
	{
		free(directories);
		directories = NULL;
	}
}
/**
 * info_toke_free - supportive functions for betty style code
 * which functions contains more than 40 line of codes
 * @info: pointes for the functions
 * Return: nothings void functions
 */
void info_toke_free(about_info *info)
{
	if (info->tokens)
	{
		free(info->tokens[0]);
	}
	info->tokens[0] = NULL;
}
