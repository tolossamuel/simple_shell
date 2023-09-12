#include "shell.h"

void free_data(data_of_program *data)
{
	if (data->tokens)
		free_array_pointes(data->tokens);
	if (data->get_line)
		free(data->get_line);
	if (data->cmd_name)
		free(data->cmd_name);

	data->get_line = NULL;	
	data->cmd_name = NULL;
	data->tokens = NULL;
}

void free_all(data_of_program *data)
{
	if (data->file_desc != 0)
	{
		if (close(data->file_desc))
			perror(data->Name_projects);
	}
	free_data(data);
	free_array_pointes(data->env);
	free_array_pointes(data->alias_list);
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
