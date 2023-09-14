#include "shell.h"

void free_data(about *info)
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

void free_all(about *info)
{
	if (info->file_desc != 0)
	{
		if (close(info->file_desc))
			perror(info->Name_projects);
	}
	free_data(info);
	free_array_pointes(info->env);
	free_array_pointes(info->alias_list);
}

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
