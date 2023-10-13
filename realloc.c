#include "shell.h"

/**
 **_memset - fills memory with a constant byte
 *@str: the pointer to the memory area
 *@a: the byte to fill ptr to string with
 *@n: the amount of bytes to be filled
 *Return: a pointer to the memory area of str
 */
char *_memset(char *str, char a, unsigned int n)
{
	unsigned int i;

	for (i = 0; i < n; i++)
		str[i] = a;
	return (str);
}

/**
 * free_argv - frees a string of strings
 * @pp_str: ptr string of ptr strings
 */
void free_argv(char **pp_str)
{
	char **mem = pp_str;

	if (!pp_str)
		return;
	while (*pp_str)
		free(*pp_str++);
	free(mem);
}

/**
 * _realloc - reallocates a block of memory for usage
 * @ptr: pointer to previous reserved memory block
 * @old_size: byte size of previous block allocated
 * @new_size: byte size of new block allocated
 *
 * Return: pointer to the new block.
 */
void *_realloc(void *ptr, unsigned int old_size, unsigned int new_size)
{
	char *ptr_2;

	if (!ptr)
		return (malloc(new_size));
	if (!new_size)
		return (free(ptr), NULL);
	if (new_size == old_size)
		return (ptr);

	ptr_2 = malloc(new_size);
	if (!ptr_2)
		return (NULL);

	old_size = old_size < new_size ? old_size : new_size;
	while (old_size--)
		ptr_2[old_size] = ((char *)ptr)[old_size];
	free(ptr);
	return (ptr_2);
}
