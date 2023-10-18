#include "shell.h"
/**
 * _strcpy - copies src pointer string including '\0' to
 *          dest buffer pointed to
 * @src: pointer to source string
 * @dest: pointer to destination
 * Return: pointer to destination
*/
void *_strcpy(char *dest, const char *src)
{
    size_t i;

    for (i = 0; src[i] != '\0'; i++)
        dest[i] = src[i];
    dest[i] = '\0';
    return (dest);
}
