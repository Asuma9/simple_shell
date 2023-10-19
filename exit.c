#include "shell.h"
/**
 * shellby_exit - function for exit
 * @args: argument checker
 * Return: 0 if success
*/
int shellby_exit(char **args)
{
    if (_strcmp(args[0], "exit") != 0)
    {
        return (-1);
    }
	if (args[1] != NULL)
	{
		_eputs("Usage: exit\n");
		return (1);
	}
	free(args);
	exit(0);
}
