#include "shell.h"

void _EOF(int size, char *buff)
{
	(void)buff;
	if (size == -1)
	{
		if (isatty(STDIN_FILENO))
		{
			free(buff);
		}
		exit(0);
	}
}

int main(int argc, char *argv[]) {
	
    char **arrays;
    char *tokenize;
    int num1;
    while (1) {
		
        size_t num2 = 0;
        char *user_input = NULL;
        int size;
        CommandFunction functions;
        if (isatty(STDIN_FILENO)) {
            print_fun("$ ");
            fflush(stdout);
        }
        size = getline_fun(&user_input, &num2, stdin);
        _EOF(size, user_input);
        user_input[string_size(user_input) - 1] = '\0';

        arrays = malloc(sizeof(char *) * num2);
        tokenize = strtok(user_input, " ");
		argc = 1;
        if (tokenize == NULL && argc) {
            free(user_input);
            continue;
        }
        num1 = 0;
        arrays[num1++] = tokenize;
        while (tokenize) {
            tokenize = strtok(NULL, " ");
            arrays[num1++] = tokenize;
        }
        functions = env_builders(arrays);
        if (functions) {
            free(user_input);
            functions(arrays);
        }

        if (access(arrays[0], X_OK) != -1) {
            int num3 = fork();
            if (num3 == 0) {
                execve(arrays[0], arrays, environ);
                perror("execve");
                exit(1);
            } else {
                wait(NULL);
            }
        } else {
            arrays[0] = search_file_path(arrays[0], split_path(file_path("PATH")));
            if (arrays[0]) {
                if (access(arrays[0], X_OK) != -1) {
                    int num3 = fork();
                    if (num3 == 0) {
                        execve(arrays[0], arrays, environ);
                        perror("execve");
                        exit(1);
                    } else {
                        wait(NULL);
                    }
                } else {
                    perror(argv[0]);
                }
            } else {
                perror(argv[0]);
            }
        }

        free(user_input);
    }
    return 0;
}