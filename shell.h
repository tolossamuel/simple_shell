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


typedef struct about
{
	char **alias_list;
	char **tokens;
	char *cmd_name;
	char *Name_projects;
	int execute_counter;
	int file_desc;
	char *get_line;
	char **env;
} about;

/**
 * env_structure - is a struct used to associate
 * built-in command names with their corresponding
 * function pointers for execution
 */
typedef struct env_structure
{
	char *built_in;
	int (*function)(about *info);
} env_structure;
void start_with(about *info, int argc, char *argv[], char **env);
void size_of_(char *prompt, about *info);
void handle_short_cut(int operations UNUSED);
int _getline(about *info);
int logical_operations(char *cmd_array[], int num, char ops_ary[]);
void var_expand(about *info);
void expand_alias(about *info);
int new_buffer(char *buffer, char *concatenate_string);
void tokenize_data(about *info);
char *str_tok(char *line, char *delim);
int executed(about *info);
int built_list(about *info);
char **path_of_file(about *info);
int search_file(about *info);
void free_array_pointes(char **array);
void free_data(about *info);
void free_all(about *info);
int exit_env(about *info);
int command_built(about *info);
int set_dir(about *info, char *new_dir);
int help_built(about *info);
int builtin_alias(about *info);
int env_builders(about *info);
int builder_set_key(about *info);
int unset_key(about *info);
char *get_key(char *key, about *info);
int set_key(char *key, char *value, about *info);
int remove_key(char *key, about *info);
void env_print(about *info);
int _print(char *string);
int _printe(char *string);
int handle_error(int error_code, about *info);
int string_size(char *string);
char *string_repetitions(char *string);
int string_comparions(char *string1, char *string2, int number);
char *string_merging(char *string1, char *string2);
void reverse(char *string);
void string_long(long number, char *string, int base);
int _atoi(char *strings);
int size_characters(char *string, char *character);
int printf_fun(about *info, char *name);
char *get_fun(about *info, char *name);
int set_fun(char *alias_string, about *info);
int check(char *file_path);

#endif /* SHELL_H */
