#ifndef SHELL_H
#define SHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>

#define MAX_ARGS 128
extern char **environ;

void print_prompt(void);
char **tokenize_input(char *line, char *delimiter);
char *find_command_in_path(char *command);
void print_env(void);
char *create_full_path(const char *dir, const char *command);
char *custom_strdup(const char *src);


#endif /* SHELL_H */
