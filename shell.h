#ifndef MAIN_H
#define MAIN_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <signal.h>
#include <errno.h>
extern char **environ;

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

typedef void (*CommandFunction)(char **);

/**
 * struct env_structure - is a struct used to associate
 * @built_in: command names with their corresponding
 * @function: pointers for execution
 */
typedef struct env_structure
{
	char *built_in;
	void (*function)(char **);
} env_structure;

char *strtok_fun(char *str, const char *delim, char **ptr_address);
ssize_t getline_fun(char **ptr_lin, size_t *num, FILE *stream);
int print_fun(char *string);
int string_size(char *string);
void check_file_status(int size, char *content);
char *string_merging(char *string_one, char *string_two);
char *string_repetitions(char *string);
void processUserInput(void);
char **split_path(char *path);
char *file_path(const char *name);
char **tokenizeInput(char *input);
void executeCommand(char **arrays);
char *search_file_path(char *filename, char **arr);
void exit_cmd(char **arr);
CommandFunction env_builders(char **arv);
#endif
