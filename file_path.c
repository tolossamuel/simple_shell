#include "shell.h"

char *file_path(const char *name)
{
    int i, j;
    char *value;

    if (!name)
        return (NULL);
    for (i = 0; environ[i]; i++)
    {
        j = 0;
        if (name[j] == environ[i][j])
        {
            while (name[j])
            {
                if (name[j] != environ[i][j])
                    break;

                j++;
            }
            if (name[j] == '\0')
            {
                value = (environ[i] + j + 1);
                return (value);
            }
        }
    }
    return (NULL); 
}

char *search_file_path(char *filename, char **arr)
{
	
	char *string;
	int num1 = 0;
	struct stat structure;

	while (arr[num1])
	{
	
		string = string_repetitions(arr[num1]);

		string = string_merging(string, "/");
		string = string_merging(string, filename);
		if (stat(string, &structure) == 0)
		{
			return (string);
		}
		free(string);
		num1++;
	}

	return (NULL);
}
