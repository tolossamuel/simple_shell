#include "shell.h"

/**
 * tokenizeInput - function tokenize a given input string
 * splitting it into an array of strings separated by spaces
 * @input: parameter of the tokenizeInput
 * Return: an array of strings (char pointers) containing
 * the tokens obtained by splitting the input string based on spaces
*/
char **tokenizeInput(char *input)
{
	char **arrays = NULL;
	char *tokenize = strtok(input, " ");
	int num1 = 0;

	if (tokenize == NULL)
	{
		return (NULL);
	}
	arrays = malloc(sizeof(char *));
	arrays[num1++] = tokenize;
	while (tokenize)
	{
		tokenize = strtok(NULL, " ");
		if (tokenize)
		{
			arrays = realloc(arrays, sizeof(char *) * (num1 + 1));
			arrays[num1++] = tokenize;
		}
	}
	return (arrays);
}

/**
 * processUserInput - function reads user input, tokenize it
 * and executes the associated command or function within
 * a continuous shell environment
 * Return: nothing void functions
*/
void processUserInput(void)
{
	char **arrays, *user_input;
	size_t num2, size;
	CommandFunction functions;

	while (1)
	{
		num2 = 0;
		user_input = NULL;
		if (isatty(STDIN_FILENO))
		{
			print_fun("$ ");
			fflush(stdout);
		}
		size = getline_fun(&user_input, &num2, stdin);
		if (size == (size_t)-1)
		{
			perror("getline");
			free(user_input);
			exit(1);
		}
		user_input[size - 1] = '\0';
		arrays = tokenizeInput(user_input);
		functions = env_builders(arrays);
		if (functions)
		{
			free(user_input);
			functions(arrays);
		}
		executeCommand(arrays);
		free(user_input);
	}
}

