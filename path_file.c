#include "shell.h"




int search_file(program_info *info)
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

	directories = path_of_file(info);/* search in the PATH */

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

char **path_of_file(program_info *info)
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