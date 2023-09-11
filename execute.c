#include "shell.h"

int executed(data_of_program *data)
{
	int num1 = 0, status;
	pid_t pid;
	num1 = builtins_list(data);
	if (num1 != -1)
		return (num1);
	num1 = search_file(data);
	if (num1)
	{
		return (num1);
	}
	else
	{
		pid = fork(); 
		if (pid == -1)
		{ 
			perror(data->cmd_name);
			exit(EXIT_FAILURE);
		}
		if (pid == 0)
		{
			num1 = execve(data->tokens[0], data->tokens, data->env);
			if (num1 == -1) 
				perror(data->cmd_name), exit(EXIT_FAILURE);
		}
		else
		{
			wait(&status);
			if (WIFEXITED(status))
				errno = WEXITSTATUS(status);
			else if (WIFSIGNALED(status))
				errno = 128 + WTERMSIG(status);
		}
	}
	return (0);
}