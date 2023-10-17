#include "shell.h"

/**
 * print_env - Prints the environment variables
 *
 * Return: void
 */

void print_env(void)
{
	/* extern environ variable is in header file */
	int env_count = 0;

	/* Loop through each environment variable and print */
	while (environ[env_count] != NULL)
	{
		write(STDOUT_FILENO, environ[env_count],
				strlen(environ[env_count]));
		write(STDOUT_FILENO, "\n", 1);
		env_count++;
	}
}
