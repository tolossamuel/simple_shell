#include "shell.h"

int _printe(char *string)
{
	return (write(STDERR_FILENO, string, string_size(string)));
}

int _print(char *string)
{
	return (write(STDOUT_FILENO, string, string_size(string)));
}

int handle_error(int error_code, program_info *info)
{
	char arr_string[10] = {'\0'};

	string_long((long) info->execute_counter, arr_string, 10);

	if (error_code == 2 || error_code == 3)
	{
		_printe(info->Name_projects);
		_printe(": ");
		_printe(arr_string);
		_printe(": ");
		_printe(info->tokens[0]);
		if (error_code == 2)
			_printe(": unexpected number: ");
		else
			_printe(": can not redirect to ");
		_printe(info->tokens[1]);
		_printe("\n");
	}
	else if (error_code == 127)
	{
		_printe(info->Name_projects);
		_printe(": ");
		_printe(arr_string);
		_printe(": ");
		_printe(info->cmd_name);
		_printe(": not found\n");
	}
	else if (error_code == 126)
	{
		_printe(info->Name_projects);
		_printe(": ");
		_printe(arr_string);
		_printe(": ");
		_printe(info->cmd_name);
		_printe(": Permission denied\n");
	}
	return (0);
}
