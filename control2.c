#include "shell.h"


char *get_key(char *key, program_info *info)
{
	int num1;
	int key_length = 0;
	if (key == NULL || info->env == NULL)
		return (NULL);
	key_length = string_size(key);

	for (num1 = 0; info->env[num1]; num1++)
	{
		if (string_comparions(key, info->env[num1], key_length) &&
		 info->env[num1][key_length] == '=')
		{
			return (info->env[num1] + key_length + 1);
		}
	}
	return (NULL);
}

int set_key(char *key, char *value, program_info *info)
{
	int i, key_length = 0, is_new_key = 1;
	if (key == NULL || value == NULL || info->env == NULL)
		return (1);
	key_length = string_size(key);

	for (i = 0; info->env[i]; i++)
	{
		if (string_comparions(key, info->env[i], key_length) &&
		 info->env[i][key_length] == '=')
		{
			is_new_key = 0;

			free(info->env[i]);
			break;
		}
	}
	info->env[i] = string_merging(string_repetitions(key), "=");
	info->env[i] = string_merging(info->env[i], value);

	if (is_new_key)
	{
		info->env[i + 1] = NULL;
	}
	return (0);
}


void env_print(program_info *info)
{
	int num1;

	for (num1 = 0; info->env[num1]; num1++)
	{
		_print(info->env[num1]);
		_print("\n");
	}
}
int remove_key(char *key, program_info *info)
{
	int num1;
	int key_length = 0;
	if (key == NULL || info->env == NULL)
		return (0);

	key_length = string_size(key);

	for (num1 = 0; info->env[num1]; num1++)
	{
		if (string_comparions(key, info->env[num1], key_length) &&
		 info->env[num1][key_length] == '=')
		{
			free(info->env[num1]);
			num1++;
			for (; info->env[num1]; num1++)
			{
				info->env[num1 - 1] = info->env[num1];
			}
			info->env[num1 - 1] = NULL;
			return (1);
		}
	}
	return (0);
}
