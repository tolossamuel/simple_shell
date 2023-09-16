#include "shell.h"

/**
 * search_file -  function searches for the existence of an executable
 * file in directories listed in the PATH environment variable and
 * updates the command path accordingly
 * @info: a pointer to a struct of type "about" that contains various
 * information about the program's execution and environment
 * Return: an exit code based on the search result of the executable file
 * in the directories listed in the PATH environment variable
 */
int search_file(about_info *info)
{
	int num1 = 0, ret_code = 0;
	char **directories;

	if (!info->cmd_name)
		return (2);
	if (info->cmd_name[0] == '/' || info->cmd_name[0] == '.')
		return (check(info->cmd_name));
	free(info->tokens[0]);
	info->tokens[0] = string_merging(string_repetitions("/"), info->cmd_name);
	if (!info->tokens[0])
		return (2);
	directories = path_of_file(info);
	if (!directories || !directories[0])
	{
		errno = 127;
		return (127);
	}
	for (num1 = 0; directories[num1]; num1++)
	{
		directories[num1] = string_merging(directories[num1], info->tokens[0]);
		ret_code = check(directories[num1]);
		if (ret_code == 0 || ret_code == 126)
		{
			errno = 0;
			free(info->tokens[0]);
			info->tokens[0] = string_repetitions(directories[num1]);
			free_array_pointes(directories);
			return (ret_code);
		}
	}
	free(info->tokens[0]);
	info->tokens[0] = NULL;
	free_array_pointes(directories);
	return (ret_code);
}

/**
 * path_of_file - extracts directories from the PATH environment variable
 * tokenize them, and returns them as an array of strings
 * @info: a pointer to a "program_info" struct in the functions
 * Return: an array of strings containing directories from the
 * PATH environment variable
*/
char **path_of_file(about_info *info)
{
	int i = 0;
	int counter_directories = 2;
	char **tokens = NULL;
	char *PATH;

	PATH = get_key("PATH", info);
	if ((PATH == NULL) || PATH[0] == '\0')
	{
		return (NULL);
	}
	PATH = string_repetitions(PATH);
	for (i = 0; PATH[i]; i++)
	{
		if (PATH[i] == ':')
			counter_directories++;
	}
	tokens = malloc(sizeof(char *) * counter_directories);
	i = 0;
	tokens[i] = string_repetitions(str_tok(PATH, ":"));
	while (tokens[i++])
	{
		tokens[i] = string_repetitions(str_tok(NULL, ":"));
	}
	free(PATH);
	PATH = NULL;
	return (tokens);
}

/**
 * check - a functions checks if a file exists and is executable
 * @file_path: a string representing the path to the file being
 * checked for existence
 * Return: 0 if the file at the specified path exists and is executable
 * 126 if it exists but is not executable, and 127 if the file does not exist
*/
int check(char *file_path)
{
	struct stat sb;

	if (stat(file_path, &sb) != -1)
	{
		if (S_ISDIR(sb.st_mode) ||  access(file_path, X_OK))
		{
			errno = 126;
			return (126);
		}
		return (0);
	}
	errno = 127;
	return (127);
}
