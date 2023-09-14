#include "shell.h"

int executed(about *info)
{
	int num1 = 0, status;
	pid_t pid;
	num1 = built_list(info);
	if (num1 != -1)
		return (num1);
	num1 = search_file(info);
	if (num1)
	{
		return (num1);
	}
	else
	{
		pid = fork(); 
		if (pid == 0)
		{
			num1 = execve(info->tokens[0], info->tokens, info->env);
			if (num1 == -1) 
				perror(info->cmd_name), exit(EXIT_FAILURE);
		}
		if (pid == -1)
		{ 
			perror(info->cmd_name);
			exit(EXIT_FAILURE);
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
