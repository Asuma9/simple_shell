#include "shell.h"
/**
 * _eputchar - writes the character c to stderr
 * @c: Character to print
 *
 * Return: 1 success, -1 error and errno is set appropriately.
 */
int _eputchar(char c)
{
	static int i;
	static char buff[1024];

	if (c == -1 || i >= 1024)
	{
		write(2, buff, i);
		i = 0;
	}
	if (c != -1)
		buff[i++] = c;
	return (1);
}
/**
 *_eputs - prints an input string to STDOUT
 * @str: ptr to string to be printed
 *
 * Return: Nothing
 */
void _eputs(char *str)
{
	int i = 0;

	if (!str)
		return;
	while (str[i] != '\0')
	{
		_eputchar(str[i]);
		i++;
	}
}
