#include "shell.h"
/**
 * _strncpy - copies src pointer string including '\0' to
 *          dest buffer pointed to
 * @src: pointer to source string
 * @dest: pointer to destination
 * @size: length of chars copied
 * Return: pointer to destination
*/
void *_strncpy(char *dest, const char *src, size_t size)
{
	size_t i;

	for (i = 0; i < size; i++)
	{
		dest[i] = src[i];
		if (src[i] == '\0')
		{
			break;
		}
	}
	return (dest);
}
/**
 * _strcmp - performs lexicogarphic comparison of two strings.
 * @s1: the first string
 * @s2: the second string
 *
 * Return: (-) if s1 < s2, (+) if if s1 > s2, (0) if s1 == s2
 */
int _strcmp(char *s1, char *s2)
{
	while (*s1 && *s2)
	{
		if (*s1 != *s2)
			return (*s1 - *s2);
		s1++;
		s2++;
	}
	if (*s1 == *s2)
		return (0);
	else
		return (*s1 < *s2 ? -1 : 1);
}
