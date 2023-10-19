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
#define BUFFER_SIZE 1024

extern char **environ;

void print_prompt(void);
char **tokenize_input(char *line, char *delimiter);
char *find_command_in_path(char *command);
void print_env(void);
char *create_full_path(const char *dir, const char *command);
char *custom_strdup(const char *src);
char *custom_getline(void);
void free_tokenized_array(char **array);
void *_strcpy(char *dest, const char *src);
void *_realloc(void *ptr, size_t old_size, size_t new_size);
void reassign_lineptr(char **lineptr, size_t *line_size, char *buffer, size_t a);
ssize_t _getline(void **lineptr, size_t *line_size);
void *_strncpy(char *dest, const char *src, size_t size);

#endif /* SHELL_H */
