#include "shell.h"

/**
 **_strncpy - copies specified number of bytes
 *@dest: the destination of the string to be copied
 *@src: the source string to be copied
 *@n: the amount of characters/bytes to be copied
 *Return: the concatenated string
 */
char *_strncpy(char *dest, char *src, int n)
{
	int i, j;
	char *con_str = dest;

	i = 0;
	while (src[i] != '\0' && i < n - 1)
	{
		dest[i] = src[i];
		i++;
	}
	if (i < n)
	{
		j = i;
		while (j < n)
		{
			dest[j] = '\0';
			j++;
		}
	}
	return (con_str);
}

/**
 **_strncat - concatenates two strings and '\0' them
 *@dest: the first string
 *@src: the second string
 *@n: the amount of bytes/mem to be maximally used
 *Return: the concatenated string
 */
char *_strncat(char *dest, char *src, int n)
{
	int i, j;
	char *con_str = dest;

	i = 0;
	j = 0;
	while (dest[i] != '\0')
		i++;
	while (src[j] != '\0' && j < n)
	{
		dest[i] = src[j];
		i++;
		j++;
	}
	if (j < n)
		dest[i] = '\0';
	return (con_str);
}

/**
 **_strchr - locates a character in a string
 *@str: the string to be parsed
 *@c: the character to search for
 *Return: a pointer to the memory area of str
 */
char *_strchr(char *str, char c)
{
	do {
		if (*str == c)
			return (str);
	} while (*str++ != '\0');

	return (NULL);
}
