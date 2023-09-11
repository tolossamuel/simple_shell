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


#include "main.h" 


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
} data_of_program;


typedef struct build_structure
{
	char *built_in;
	int (*function)(data_of_program *data);
} build_structure;
void start_with(data_of_program *data, int arc, char *argv[], char **env);
void size_of_(char *prompt, data_of_program *data);
void handle_short_cut(int opr UNUSED);
int _getline(data_of_program *data);
int logical_operations(char *array_commands[], int i, char array_operators[]);
void var_expand(data_of_program *data);
void expand_alias(data_of_program *data);
int new_buffer(char *buffer, char *str_to_add);
void tokenize_data(data_of_program *data);
char *str_tok(char *line, char *delim);
int executed(data_of_program *data);
int builtins_list(data_of_program *data);
char **path_of_file(data_of_program *data);
int search_file(data_of_program *data);
void free_array_pointes(char **directories);
void free_data(data_of_program *data);
void free_all(data_of_program *data);
int builtin_exit(data_of_program *data);
int builtin_cd(data_of_program *data);
int set_work_directory(data_of_program *data, char *new_dir);
int builtin_help(data_of_program *data);
int builtin_alias(data_of_program *data);
int env_builders(data_of_program *data);
int builder_set_key(data_of_program *data);
int unset_key(data_of_program *data);
char *get_key(char *name, data_of_program *data);
int set_key(char *key, char *value, data_of_program *data);
int remove_key(char *key, data_of_program *data);
void env_print(data_of_program *data);
int _print(char *string);
int _printe(char *string);
int handle_error(int error_code, data_of_program *data);
int string_size(char *string);
char *string_repetitions(char *string);
int string_comparions(char *string1, char *string2, int number);
char *string_merging(char *string1, char *string2);
void reverse(char *string);
void string_long(long number, char *string, int base);
int _atoi(char *s);
int size_characters(char *string, char *character);
int printf_fun(data_of_program *data, char *alias);
char *get_functions(data_of_program *data, char *alias);
int set_functions(char *alias_string, data_of_program *data);
int check(char *full_path);
#endif /* SHELL_H */