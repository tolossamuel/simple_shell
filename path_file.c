#include "shell.h"




int search_file(data_of_program *data)
{
	int i = 0, ret_code = 0;
	char **directories;

	if (!data->cmd_name)
		return (2);
	if (data->cmd_name[0] == '/' || data->cmd_name[0] == '.')
		return (check(data->cmd_name));

	free(data->tokens[0]);
	data->tokens[0] = string_merging(string_repetitions("/"), data->cmd_name);
	if (!data->tokens[0])
		return (2);

	directories = path_of_file(data);/* search in the PATH */

	if (!directories || !directories[0])
	{
		errno = 127;
		return (127);
	}
	for (i = 0; directories[i]; i++)
	{
		directories[i] = string_merging(directories[i], data->tokens[0]);
		ret_code = check(directories[i]);
		if (ret_code == 0 || ret_code == 126)
		{
			errno = 0;
			free(data->tokens[0]);
			data->tokens[0] = string_repetitions(directories[i]);
			free_array_pointes(directories);
			return (ret_code);
		}
	}
	free(data->tokens[0]);
	data->tokens[0] = NULL;
	free_array_pointes(directories);
	return (ret_code);
}

char **path_of_file(data_of_program *data)
{
	int i = 0;
	int counter_directories = 2;
	char **tokens = NULL;
	char *PATH;
	PATH = get_key("PATH", data);
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

int check(char *full_path)
{
	struct stat sb;

	if (stat(full_path, &sb) != -1)
	{
		if (S_ISDIR(sb.st_mode) ||  access(full_path, X_OK))
		{
			errno = 126;
			return (126);
		}
		return (0);
	}
	errno = 127;
	return (127);
}