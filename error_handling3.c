#include "shell.h"

int _print(char *string)
{
	return (write(STDOUT_FILENO, string, string_size(string)));
}

int _printe(char *string)
{
	return (write(STDERR_FILENO, string, string_size(string)));
}


int handle_error(int error_code, data_of_program *data)
{
	char n_as_string[10] = {'\0'};

	string_long((long) data->execute_counter, n_as_string, 10);

	if (error_code == 2 || error_code == 3)
	{
		_printe(data->Name_projects);
		_printe(": ");
		_printe(n_as_string);
		_printe(": ");
		_printe(data->tokens[0]);
		if (error_code == 2)
			_printe(": unexpected number: ");
		else
			_printe(": can not redirect to ");
		_printe(data->tokens[1]);
		_printe("\n");
	}
	else if (error_code == 127)
	{
		_printe(data->Name_projects);
		_printe(": ");
		_printe(n_as_string);
		_printe(": ");
		_printe(data->cmd_name);
		_printe(": not found\n");
	}
	else if (error_code == 126)
	{
		_printe(data->Name_projects);
		_printe(": ");
		_printe(n_as_string);
		_printe(": ");
		_printe(data->cmd_name);
		_printe(": Permission denied\n");
	}
	return (0);
}
