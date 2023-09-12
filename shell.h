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
} program_info;


typedef struct env_structure
{
	char *built_in;
	int (*function)(program_info *info);
} env_structure;
void start_with(program_info *info, int arc, char *argv[], char **env);
void size_of_(char *prompt, program_info *info);
void handle_short_cut(int opr UNUSED);
int _getline(program_info *info);
int logical_operations(char *cmd_array[], int num, char ops_ary[]);
void var_expand(program_info *info);
void expand_alias(program_info *info);
int new_buffer(char *buffer, char *str_to_add);
void tokenize_data(program_info *info);
char *str_tok(char *line, char *delim);
int executed(program_info *info);
int built_list(program_info *info);
char **path_of_file(program_info *info);
int search_file(program_info *info);
void free_array_pointes(char **directories);
void free_data(program_info *info);
void free_all(program_info *info);
int exit_env(program_info *info);
int command_built(program_info *info);
int set_dir(program_info *info, char *new_dir);
int help_built(program_info *info);
int builtin_alias(program_info *info);
int env_builders(program_info *info);
int builder_set_key(program_info *info);
int unset_key(program_info *info);
char *get_key(char *name, program_info *info);
int set_key(char *key, char *value, program_info *info);
int remove_key(char *key, program_info *info);
void env_print(program_info *info);
int _print(char *string);
int _printe(char *string);
int handle_error(int error_code, program_info *info);
int string_size(char *string);
char *string_repetitions(char *string);
int string_comparions(char *string1, char *string2, int number);
char *string_merging(char *string1, char *string2);
void reverse(char *string);
void string_long(long number, char *string, int base);
int _atoi(char *s);
int size_characters(char *string, char *character);
int printf_fun(program_info *info, char *alias);
char *get_fun(program_info *info, char *alias);
int set_fun(char *alias_string, program_info *info);
int check(char *full_path);




#endif /* SHELL_H */