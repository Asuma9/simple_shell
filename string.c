#include "shell.h"
/**
 * _strcpy - copies src pointer string including '\0' to
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
