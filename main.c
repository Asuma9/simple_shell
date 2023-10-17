#include "shell.h"

/**
 * handle_command - Handles the command execution
 * @argv: The tokenized input
 *
 * Return: The exit status of the command
 */
int handle_command(char **argv)
{
	int status;
	pid_t child_pid;
	char *command_path = find_command_in_path(argv[0]);

	if (!command_path)
	{
		write(STDERR_FILENO, "./hsh: 1: ", 10);
		write(STDERR_FILENO, argv[0], strlen(argv[0]));
		write(STDERR_FILENO, ": not found\n", 12);
		free(argv);
		return (127);
	}
	child_pid = fork();

	if (child_pid == -1)
	{
		perror("Error");
		free(argv);
		free(command_path);
		return (1);
	}
	if (child_pid == 0)
	{
		/*extern char **environ;*/

		if (execve(command_path, argv, environ) == -1)
		{
			perror("Error");
			exit(1);
		}
	}
	else
	{
		wait(&status);
		if (WIFEXITED(status))
			return (WEXITSTATUS(status));
	}
	free(argv);
	free(command_path);
	return (0);
}

/**
 * read_and_execute - Reads a line and executes the command
 *
 * Return: The exit status of the command
 */

int read_and_execute(void)
{
	char *line = NULL;
	size_t len = 0;
	ssize_t nread, len_without_nulls;
	char **argv = NULL;
	int exit_status;

	print_prompt();
	nread = getline(&line, &len, stdin);
	if (nread == -1)
	{
		free(line);
		return (-1);
	}
	len_without_nulls = strcspn(line, "\0");

	line[len_without_nulls] = '\0';
	line[nread - 1] = '\0';
	if (strcmp(line, "exit") == 0 || strcmp(line, "env") == 0)
	{
		if (strcmp(line, "env") == 0)
			print_env();
		free(line);
		return (-1);
	}
	argv = tokenize_input(line, " \t\r\n");

	if (!argv[0] || argv[0][0] == '\0')
	{
		free(argv);
		return (0);
	}
	exit_status = handle_command(argv);

	return (exit_status);
}

/**
 * main - Main function for the shell
 *
 * Return: 0 on success, 1 on failure
 */
int main(void)
{
	int last_exit_status = 0;

	while (1)
	{
		int status = read_and_execute();

		if (status == -1)
			break;
		last_exit_status = status;
		if (status != 0)
			break;
		continue;
	}
	return (last_exit_status);
}
