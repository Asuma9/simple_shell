#ifndef _SHELL_H_
#define _SHELL_H_

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <limits.h>
#include <fcntl.h>
#include <errno.h>

/* for read/write to buffer(size) */
#define READ_BUF_SIZE 1024
#define WRITE_BUF_SIZE 1024
#define BUF_FLUSH -1

/* for command chaining */
#define CMD_NORM	0 /*exec normally(no && || etc)*/
#define CMD_OR		1 /*|| exec if prev cmd fails*/
#define CMD_AND		2 /* && exec if prev cmd succeds*/
#define CMD_CHAIN	3 /* exec all sequenced cmds */

/* to convert_number() */
#define CONVERT_LOWERCASE	1
#define CONVERT_UNSIGNED	2

/* 1 if using system getline() or strtok() */
#define USE_GETLINE 0
#define USE_STRTOK 0

#define HIST_FILE	".simple_shell_history"
#define HIST_MAX	1024

/* environment variables */
extern char **environ; /*'PATH','HOME','USER'*/

/* Data structure 1 definition*/
/**
 * struct list_str - singly linked list
 * @num: the number field
 * @str: ptr to a string
 * @next: points to the next node
 */
typedef struct list_str
{
	int num;
	char *str;
	struct list_str *next;
} list_t;

/* Data structure 2 definition*/
/**
 *struct shellinfo - contains implemention arguments to pass into a function,
 *		allowing uniform prototype for function pointer struct
 *@arg: ptr to string generated from getline containing command arguments
 *@argv: an array of strings representing arguments
 *@path: a string path for the current command
 *@argc: the argument counter
 *@line_size: tracks line size
 *@err_num: the error code for exit(s)
 *@linesize_flag: flags line size counting
 *@fname: the program filename
 *@env: linked list for storing environment variables
 *@environ: custom modified copy of environ variables
 *@history: linked list for storing command history
 *@alias: linked list for storing aliases
 *@env_changed: tracks changes to the environment
 *@status: stores return status of the last exec'd command
 *@cmd_buff: address of pointer to cmd_buf, for chaining
 *@cmd_buf_type: reps type of comm chaining(NORM, ||, &&, ;)
 *@r_filedes: file descriptor for reading line input
 *@histcount: counts the history line number
 */
typedef struct shellinfo
{
	int argc;
	int err_num;
	int linesize_flag;
	unsigned int line_size;
	int env_changed;
	int status;
	int cmd_buf_type; /* NORMAL, ||, &&, ; */
	int r_filedes;
	int histcount;
	char *arg;
	char **argv;
	char *path;
	char *fname;
	list_t *env;
	list_t *history;
	list_t *alias;
	char **environ;
	char **cmd_buff; /* pointer to cmd ; chain buffer, for memory management */
} info_t;

#define INFO_INIT \
{0, 0, 0, 0, 0, 0, 0, 0, 0, NULL, NULL, NULL, NULL, NULL, NULL, NULL, \
NULL, NULL}

/* managing builtin commands and associated function calls*/
/**
 *struct builtin - contains a builtin string and related function
 *@type: pointer to a builtin command
 *@func: stores a ptr to associated function to be executed
 */
typedef struct builtin
{
	char *type;
	int (*func)(info_t *);
} builtin_table;


/* fname_shloop.c */
int _shell(info_t *, char **);
int find_builtin(info_t *);
void find_cmd(info_t *);
void fork_cmd(info_t *);

/* fname_parser.c */
int is_exec(info_t *, char *);
char *dup_chars(char *, int, int);
char *find_path(info_t *, char *, char *);

/* fname_loophsh.c */
int loophsh(char **);

/* fname_errors.c */
void _eputs(char *);
int _eputchar(char);
int _putfd(char c, int fd);
int _putsfd(char *str, int fd);

/* fname_string.c */
int _strlen(char *);
int _strcmp(char *, char *);
char *starts_with(const char *, const char *);
char *_strcat(char *, char *);

/* fname_string1.c */
char *_strcpy(char *, char *);
char *_strdup(const char *);
void _puts(char *);
int _putchar(char);

/* fname_exits.c */
char *_strncpy(char *, char *, int);
char *_strncat(char *, char *, int);
char *_strchr(char *, char);

/* fname_tokenizer.c */
char **_strtow(char *, char *);
char **_strtow1(char *, char);

/* fname_realloc.c */
char *_memset(char *, char, unsigned int);
void free_argv(char **);
void *_realloc(void *, unsigned int, unsigned int);

/* mem management fname_memory.c */
int free_buf(void **);

/* fname_atoi.c */
int interactive(info_t *);
int is_delim(char, char *);
int _isalpha(int);
int _atoi(char *);

/* fname_errors1.c */
int _erratoi(char *);
void print_error(info_t *, char *);
int print_dec(int, int);
char *convert_num(long int, int, int);
void remove_comments(char *);

/* fname_builtin.c */
int _myexit(info_t *);
int _mycd(info_t *);
int _myhelp(info_t *);

/* fname_builtin1.c */
int _myhistory(info_t *);
int _myalias(info_t *);

/* fname_getline.c */
ssize_t input_handle(info_t *, char **, size_t *);
ssize_t get_input(info_t *);
ssize_t read_buf(info_t *, char *, size_t *);
int _getline(info_t *, char **, size_t *);
void sigintHandler(int);

/* fname_getinfo.c */
void clear_info(info_t *);
void set_info(info_t *, char **);
void free_info(info_t *, int);

/* fname_environ.c */
char *_getenv(info_t *, const char *);
int _myenv(info_t *);
int _mysetenv(info_t *);
int _myunsetenv(info_t *);
int populate_env_list(info_t *);

/* fname_getenv.c */
char **get_environ(info_t *);
int _unsetenv(info_t *, char *);
int _setenv(info_t *, char *, char *);

/* fname_history.c */
char *get_hist_file(info_t *info);
int write_history(info_t *info);
int read_history(info_t *info);
int build_hist_list(info_t *info, char *buf, int linecount);
int renumber_hist(info_t *info);

/* fname_lists.c */
list_t *add_node_head(list_t **, const char *, int);
list_t *add_node_tail(list_t **, const char *, int);
size_t print_list_str(const list_t *);
int delete_node_n(list_t **, unsigned int);
void free_list(list_t **);

/* fname_lists1.c */
size_t list_len(const list_t *);
char **list_to_strings(list_t *);
size_t print_list(const list_t *);
list_t *node_starts_with(list_t *, char *, char);
ssize_t get_node_index(list_t *, list_t *);

/* fname_vars.c */
int is_chain(info_t *, char *, size_t *);
void check_chain(info_t *, char *, size_t *, size_t, size_t);
int replace_alias(info_t *);
int replace_vars(info_t *);
int replace_string(char **, char *);

#endif /* _SHELL_*/
