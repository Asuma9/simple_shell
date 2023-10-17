#include "shell.h"

#define BUFFER_SIZE 1024

/**
 * custom_getline - reads a line from stdin and returns it.
 *
 * Return: A pointer to the line read, or NULL on failure or EOF.
 */
char *custom_getline(void)
{
	char *buffer = malloc(sizeof(char) * BUFFER_SIZE);
	int c;
	size_t i = 0;

	if (!buffer)
		return (NULL);
	while (1)
	{
		if (i % BUFFER_SIZE == 0 && i != 0)
		{
			char *new_buffer = realloc(buffer,
					sizeof(char) * (i + BUFFER_SIZE));
			if (!new_buffer)
			{
				free(buffer);
				return (NULL);
			}
			buffer = new_buffer;
		}
		c = getchar();
		if (c == EOF || c == '\n')
			break;
		buffer[i++] = c;
	}
	buffer[i] = '\0';
	if (i == 0) /* buffer is empty */
	{
		free(buffer);
		return (NULL);
	}
	return (buffer);
}
