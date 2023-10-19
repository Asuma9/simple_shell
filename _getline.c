#include "shell.h"
/**
 * _realloc - realocates mem block using malloc and free
 * @ptr: pointer to mem previously allocated
 * @old_size: previous size in bytes alloc for ptr
 * @new_size: size in bytes for new mem block
 * Return: ptr if new_size == old_size
 *          NULL if new_size == 0
 *          pointer to reallocated memory block
*/
void *_realloc(void *ptr, size_t old_size, size_t new_size)
{
	void *buffer;
	size_t copy_size;

	if (new_size == old_size)
		return (ptr);

	if (ptr == NULL)
	{
		buffer = (char *)malloc(new_size);
		if (buffer == NULL)
			return (NULL);
		return (buffer);
	}

	if (new_size == 0)
	{
		free(ptr);
		return (NULL);
	}

	buffer = malloc(new_size);
	if (buffer == NULL)
		return (NULL);

	copy_size = (old_size < new_size) ? old_size : new_size;
	_strncpy(buffer, ptr, copy_size);

	free(ptr);
	return (buffer);
}


/**
 * _getline - gets input from input stream
 * @lineptr: A buffer to store the input from stream
 * @line_size: The size of lineptr
 * @stream: The stream to read from
 * Return: Number of bytes read
*/
static char buffer[BUFFER_SIZE];
static size_t buffer_index = 0;

ssize_t _getline(void **lineptr, size_t *line_size)
{
	ssize_t ret_val, read_bytes;
	char c;
	size_t line_len = 0;
	size_t max_line_len = BUFFER_SIZE;

	if (*lineptr == NULL)
	{
		*lineptr = (char *)malloc(max_line_len);
		if (*lineptr == NULL)
			return (-1);
		*line_size = max_line_len;
	}
	while (1)
	{
		if (buffer_index == 0)
		{
			read_bytes = read(STDIN_FILENO, buffer, BUFFER_SIZE);
			if (read_bytes <= 0)
				return (read_bytes); /* Handles read errors or EOF*/

			buffer_index = 0;
		}
		c = buffer[buffer_index];/*reading chars from the buffer*/
		buffer_index++;
		if (line_len + 1 >= max_line_len)/* Reading more input dynamically*/
		{
			max_line_len *= 2; /* doubling max length*/
			*lineptr = (char *)_realloc(*lineptr, *line_size, max_line_len);
			if (*lineptr == NULL)
				return (-1);
			*line_size = max_line_len;
		}
		((char *) (*lineptr))[line_len] = c;
		line_len++;
		((char *)(*lineptr))[line_len] = '\0'; /* Null-terminate the line */
		if (c == '\n')
			break; /* End of line */
	}
	ret_val = line_len; /* update with no of chars read*/
	return (ret_val);
}
