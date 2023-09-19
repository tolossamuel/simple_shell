#include "shell.h"

int print_fun(char *string)
{
	return (write(STDERR_FILENO, string, string_size(string)));
}

int string_size(char *string)
{
	int counter = 0;

	if (string == NULL)
		return (0);
	while (string[counter++] != '\0')
	{
	}
	return (counter - 1);
}

ssize_t getline_fun(char **ptr_lin, size_t *num1, FILE *stream) {
    size_t store = *num1;
    size_t i = 0;
    int c;
	char *temp;
    if (*ptr_lin == NULL) {
        *ptr_lin = (char *)malloc(store);
        if (*ptr_lin == NULL) {
            return -1;
        }
    }

    while ((c = fgetc(stream)) != EOF) {
        if (i >= store - 1) {
            store *= 2;
            temp = (char *)realloc(*ptr_lin, store);
            if (temp == NULL) {
                return -1;
            }
            *ptr_lin = temp;
            *num1 = store;
        }

        (*ptr_lin)[i++] = (char)c;

        if (c == '\n') {
            break;
        }
    }

    if (i == 0 && c == EOF) {
        return -1;  
    }

    (*ptr_lin)[i] = '\0'; 
    return i;
}