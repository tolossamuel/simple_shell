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
typedef struct env_structure
{
	char *built_in;
	void (*function)(char **);
} env_structure;

char *strtok_fun(char *str, const char *delim, char **ptr_address);
ssize_t getline_fun(char **ptr_lin, size_t *num, FILE *stream);
int print_fun(char *string);
int string_size(char *string);
char *string_merging(char *string_one, char *string_two);
char *string_repetitions(char *string);


char **split_path(char *path);
char *file_path(const char *name);
char *search_file_path(char *filename, char **arr);
void exit_cmd(char **arr);
CommandFunction env_builders(char **arv);

#endif 
