#include "shell.h"


char *get_key(char *key, data_of_program *data)
{
	int num1;
	int key_length = 0;
	if (key == NULL || data->env == NULL)
		return (NULL);
	key_length = string_size(key);

	for (num1 = 0; data->env[num1]; num1++)
	{
		if (string_comparions(key, data->env[num1], key_length) &&
		 data->env[num1][key_length] == '=')
		{
			return (data->env[num1] + key_length + 1);
		}
	}
	return (NULL);
}

int set_key(char *key, char *value, data_of_program *data)
{
	int i, key_length = 0, is_new_key = 1;
	if (key == NULL || value == NULL || data->env == NULL)
		return (1);
	key_length = string_size(key);

	for (i = 0; data->env[i]; i++)
	{
		if (string_comparions(key, data->env[i], key_length) &&
		 data->env[i][key_length] == '=')
		{
			is_new_key = 0;

			free(data->env[i]);
			break;
		}
	}
	data->env[i] = string_merging(string_repetitions(key), "=");
	data->env[i] = string_merging(data->env[i], value);

	if (is_new_key)
	{
		data->env[i + 1] = NULL;
	}
	return (0);
}


int remove_key(char *key, data_of_program *data)
{
	int num1;
	int key_length = 0;
	if (key == NULL || data->env == NULL)
		return (0);

	key_length = string_size(key);

	for (num1 = 0; data->env[num1]; num1++)
	{
		if (string_comparions(key, data->env[num1], key_length) &&
		 data->env[num1][key_length] == '=')
		{
			free(data->env[num1]);
			num1++;
			for (; data->env[num1]; num1++)
			{
				data->env[num1 - 1] = data->env[num1];
			}
			data->env[num1 - 1] = NULL;
			return (1);
		}
	}
	return (0);
}

void env_print(data_of_program *data)
{
	int num1;

	for (num1 = 0; data->env[num1]; num1++)
	{
		_print(data->env[num1]);
		_print("\n");
	}
}