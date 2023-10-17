#include "shell.h"

/**
 * print_prompt - Prints the prompt
 *
 * Return: void
 */
void print_prompt(void)
{
	/* This was causing errors, removed it temporarily */
	if (isatty(STDIN_FILENO))
	{
		write(STDOUT_FILENO, "$", 1);
	}
}

/**
 * tokenize_input - Tokenizes the input line based on a delimiter
 * @line: The input line to tokenize
 * @delimiter: The delimiter to tokenize the line
 *
 * Return: A pointer to an array of tokens
 */
char **tokenize_input(char *line, char *delimiter)
{
	int idx = 0;
	char **tokens = malloc(MAX_ARGS * sizeof(char *));
	char *token;

	if (!tokens)
	{
		perror("Error");
		exit(1);
	}

	token = strtok(line, delimiter);
	while (token != NULL)
	{
		tokens[idx] = token;
		idx++;
		token = strtok(NULL, delimiter);
	}

	tokens[idx] = NULL;
	return (tokens);
}
