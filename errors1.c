#include "shell.h"

/**
 * _erratoi - converts a string to an integer
 * @str: the string to be converted to an integer
 * Return: 0 if no numbers in string, converted number otherwise
 *       -1 on error
 */
int _erratoi(char *str)
{
	int i = 0;
	unsigned long int output = 0;

	if (*str == '+')
		str++;
	for (i = 0;  str[i] != '\0'; i++)
	{
		if (str[i] >= '0' && str[i] <= '9')
		{
			output *= 10;
			output += (str[i] - '0');
			if (output > INT_MAX)
				return (-1);
		}
		else
			return (-1);
	}
	return (output);
}

/**
 * print_error - prints an error message
 * @info: info structure address (ptr to). Used to maintain
 *        constant function prototype
 * @str: string containing specified error type
 * Return: 0 if str empty, converted number otherwise
 *        -1 on error
 */
void print_error(info_t *info, char *str)
{
	_eputs(info->fname);
	_eputs(": ");
	print_dec(info->line_size, STDERR_FILENO);
	_eputs(": ");
	_eputs(info->argv[0]);
	_eputs(": ");
	_eputs(str);
}

/**
 * print_dec - function prints a decimal (integer) number (at base 10)
 * @input: the input
 * @filedes: the filedescriptor to write to
 *
 * Return: number of characters printed
 */
int print_dec(int input, int filedes)
{
	int (*__putchar)(char) = _putchar;
	int i, decimal = 0;
	unsigned int _abs, current;

	if (filedes == STDERR_FILENO)
		__putchar = _eputchar;
	if (input < 0)
	{
		_abs = -input;
		__putchar('-');
		decimal++;
	}
	else
		_abs = input;
	current = _abs;
	for (i = 1000000000; i > 1; i /= 10)
	{
		if (_abs / i)
		{
			__putchar('0' + current / i);
			decimal++;
		}
		current %= i;
	}
	__putchar('0' + current);
	decimal++;

	return (decimal);
}

/**
 * convert_num - converter function, a clone of _itoa
 * @num: number to convert
 * @base: given base
 * @flags: argument flags
 *
 * Return: string
 */
char *convert_num(long int num, int base, int flags)
{
	static char *arr;
	static char buff[50];
	char sign = 0;
	char *ptr;
	unsigned long n = num;

	if (!(flags & CONVERT_UNSIGNED) && num < 0)
	{
		n = -num;
		sign = '-';

	}
	arr = flags & CONVERT_LOWERCASE ? "0123456789abcdef" : "0123456789ABCDEF";
	ptr = &buff[49];
	*ptr = '\0';

	do	{
		*--ptr = arr[n % base];
		n /= base;
	} while (n != 0);

	if (sign)
		*--ptr = sign;
	return (ptr);
}

/**
 * remove_comments - function replaces first instance of '#' with '\0'
 * @buff: address of the string to modify
 *
 * Return: 0 Always;
 */
void remove_comments(char *buff)
{
	int i;

	for (i = 0; buff[i] != '\0'; i++)
		if (buff[i] == '#' && (!i || buff[i - 1] == ' '))
		{
			buff[i] = '\0';
			break;
		}
}
