#include "shell.h"

/**
 * get_key - Retrieve the value of an environment
 * variable based on the provided key
 * @key: a string representing the environment variable key
 * @info: a pointer to a structure likely holding
 * program-related information
 * Return: a pointer to the value of the specified environment
 * variable or NULL if the variable is not found
 */
char *get_key(char *key, about_info *info)
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
/**
 * set_key - Set an environment variable with a specified
 * key and value or update an existing one
 * @key: a string representing the environment variable key
 * @value: a string representing the environment variable value
 * @info: a pointer to a structure likely holding
 * program-related information
 * Return: 0 on success and 1 on failure
 */
int set_key(char *key, char *value, about_info *info)
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

/**
 * env_print - Print the list of environment variables
 * @info: a pointer to a structure likely holding
 * program-related information
 * Return: nothing
 */
void env_print(about_info *info)
{
	int num1;

	for (num1 = 0; info->env[num1]; num1++)
	{
		_print(info->env[num1]);
		_print("\n");
	}
}

/**
 * remove_key - Remove an environment variable based on the provided key
 * @info: a pointer to a structure likely holding
 * program-related information
 * @key: a string representing the environment variable key
 * Return: zero (0)
 */
int remove_key(char *key, about_info *info)
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
