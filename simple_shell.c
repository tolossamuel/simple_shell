#include "shell.h"

/**
 * main - function initializes a program structure
 * Return: zero (0)
*/
int main(void)
{
	processUserInput();
	return (0);
}

/**
 * executeCommand - It checks if the first element of the arrays
 * parameter is an executable file (accessible for execution)
 * @arrays: A pointer to an array of strings (char pointers)
 * typically representing command-line arguments
 * Return: nothing it void functions
*/
void executeCommand(char **arrays)
{
	int num3;
	char *path;

	if (access(arrays[0], X_OK) != -1)
	{
		num3 = fork();
		if (num3 == 0)
		{
			execve(arrays[0], arrays, environ);
			perror("execve");
			exit(1);
		} else
		{
			wait(NULL);
		}
	} else
	{
		path = search_file_path(arrays[0], split_path(file_path("PATH")));
		if (path)
		{
			if (access(path, X_OK) != -1)
			{
				num3 = fork();
				if (num3 == 0)
				{
					execve(path, arrays, environ);
					perror("execve");
					exit(1);
				} else
				{
					wait(NULL);
				}
			} else
				perror(arrays[0]);
			free(path);
		} else
			perror(arrays[0]);
	}
}
