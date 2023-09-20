#include "shell.h"

/**
 * main - function initializes a program structure
 * Return: zero (0)
*/
int main(int argc, char *argv[])
{
    
    char *executable_name = strrchr(argv[0], '/');
	char *prompt;
	argc = 1;
    if (executable_name && argc) {
        executable_name++; 
    } else {
        executable_name = argv[0]; 
    }

    prompt = malloc(strlen(executable_name) + 1); 
    if (prompt == NULL) {
        perror("malloc");
        return 1;
    }

    strcpy(prompt, executable_name);

    processUserInput(argv[0]);

    free(prompt);
    return 0;
}

/**
 * executeCommand - It checks if the first element of the arrays
 * parameter is an executable file (accessible for execution)
 * @arrays: A pointer to an array of strings (char pointers)
 * typically representing command-line arguments
 * Return: nothing it void functions
*/
void executeCommand(char **arrays, char *symbol)
{
    int num3;
    char *path;

    if (arrays == NULL || arrays[0] == NULL)
    {
        
        return; 
    }

    if (access(arrays[0], X_OK) != -1)
    {
        num3 = fork();
        if (num3 == 0)
        {
            execve(arrays[0], arrays, environ);
            perror("execve");
            exit(1);
        }
        else
        {
            wait(NULL);
        }
    }
    else
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
                }
                else
                {
                    wait(NULL);
                }
            }
            else
                perror(arrays[0]);
            free(path);
        }
        else
            perror(symbol);
    }
}
