#include "shell.h"

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

/**
 * _eputchar - writes the character c to stderr
 * @c: Character to print
 *
 * Return: 1 success, -1 error and errno is set appropriately.
 */
int _eputchar(char c)
{
	static int i;
	static char buff[WRITE_BUF_SIZE];

	if (c == BUF_FLUSH || i >= WRITE_BUF_SIZE)
	{
		write(2, buff, i);
		i = 0;
	}
	if (c != BUF_FLUSH)
		buff[i++] = c;
	return (1);
}

/**
 * _putfd - writes the character c to given file descriptor
 * @c: The character to write
 * @filedes: The filedescriptor to write to
 *
 * Return: 1 success, -1 error and errno is set appropriately.
 */
int _putfd(char c, int filedes)
{
	static int i;
	static char buff[WRITE_BUF_SIZE];

	if (c == BUF_FLUSH || i >= WRITE_BUF_SIZE)
	{
		write(filedes, buff, i);
		i = 0;
	}
	if (c != BUF_FLUSH)
		buff[i++] = c;
	return (1);
}

/**
 *_putsfd - prints an input string to given file descriptor
 * @str: the string to be printed
 * @filedes: the filedescriptor to write to
 *
 * Return: the number of chars printed
 */
int _putsfd(char *str, int filedes)
{
	int i = 0;

	if (!str)
		return (0);
	while (*str)
	{
		i += _putfd(*str++, filedes);
	}
	return (i);
}
