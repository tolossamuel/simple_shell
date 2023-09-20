#ifndef SHELL_H
#define SHELL_H

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <stddef.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <signal.h>
#include <fcntl.h>

#define PROMPT_MSG "$ "

#define UNUSED __attribute__((unused))
#define BUFFER_SIZE 1024
#define HELP_SETENV_MSG "setenv command:\n"
#define HELP_ENV_MSG "env command:\n"
#define HELP_CD_MSG "cd command:\n"
#define HELP_EXIT_MSG "exit command:\n"
#define HELP_UNSETENV_MSG "unsetenv command:\n"
#define HELP_MSG "help command:\n"

/**
 * struct about_info - pattern for the simple shell
 * @alias_list: An array of strings to store alias definitions
 * @tokens: An array of strings to store command tokens
 * @cmd_name: A string representing the command name
 * @name_projects: A string representing the name of the project
 * @execute_counter: An integer to keep track of the execution count
 * @file_desc: An integer representing a file descriptor
 * @get_line:  A string to store a line of input
 * @env: An array of strings to store environment variables
 */
typedef struct about_info
{
	char **alias_list;
	char **tokens;
	char *cmd_name;
	char *name_projects;
	int execute_counter;
	int file_desc;
	char *get_line;
	char **env;
} about_info;

/**
 * struct env_structure - is a struct used to associate
 * @built_in: command names with their corresponding
 * @function: pointers for execution
 */
typedef struct env_structure
{
	char *built_in;
	int (*function)(about_info *info);
} env_structure;
void start_with(about_info *info, int argc, char *argv[], char **env);
void size_of_(char *prompt, about_info *info);
void handle_short_cut(int operations UNUSED);
int _getline(about_info *info);
int logical_operations(char *cmd_array[], int num, char ops_ary[]);
void var_expand(about_info *info);
void expand_alias(about_info *info);
int new_buffer(char *buffer, char *concatenate_string);
void tokenize_data(about_info *info);
char *str_tok(char *line, char *delim);
int executed(about_info *info);
int built_list(about_info *info);
char **path_of_file(about_info *info);
int search_file(about_info *info);
void free_array_pointes(char **array);
void free_data(about_info *info);
void free_all(about_info *info);
int exit_env(about_info *info);
int command_built(about_info *info);
int set_dir(about_info *info, char *new_dir);
int help_built(about_info *info);
int builtin_alias(about_info *info);
int env_builders(about_info *info);
int builder_set_key(about_info *info);
int unset_key(about_info *info);
char *get_key(char *key, about_info *info);
int set_key(char *key, char *value, about_info *info);
int remove_key(char *key, about_info *info);
void env_print(about_info *info);
int _print(char *string);
int _printe(char *string);
int handle_error(int error_code, about_info *info);
int string_size(char *string);
char *string_repetitions(char *string);
int string_comparions(char *string1, char *string2, int number);
char *string_merging(char *string1, char *string2);
void reverse(char *string);
void string_long(long number, char *string, int base);
int _atoi(char *strings);
int size_characters(char *string, char *character);
int printf_fun(about_info *info, char *name);
char *get_fun(about_info *info, char *name);
int set_fun(char *alias_string, about_info *info);
int check(char *file_path);

#endif /* SHELL_H */
