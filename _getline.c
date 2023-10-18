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
void *_realloc(void *ptr, unsigned int old_size, unsigned int new_size)
{
    void *buffer;
    char *ptr_cpy, *filler;
    unsigned int count;

    if (new_size == old_size)
        return (ptr);
    if (ptr == NULL)
    {
        buffer = malloc(new_size);
        if (buffer == NULL)
            return (NULL);

        return (buffer);
    }
    if (new_size == 0 && ptr != NULL)
    {
        free(ptr);
        return (NULL);
    }
    ptr_cpy = ptr;
    buffer = malloc(sizeof(*ptr_cpy) * new_size);
    if (buffer == NULL)
    {
        free(ptr);
        return (NULL);
    }
    filler = buffer;
    for (count = 0; count < old_size && count < new_size; count++)
        filler[count] = *ptr_cpy;
    free(ptr);
    return (buffer);
}
/**
 * reassign_lineptr - reassigns lineptr var for _getline
 * @lineptr: buffer to store input string
 * @str: string to assign to lineptr
 * @line_size: size of lineptr
 * @b: size of buffer
*/
void reassign_lineptr(char **lineptr, size_t *line_size, char *buffer, size_t a)
{
    if (*lineptr == NULL)
    {
        if (a > 120)
            *line_size = a;
        else
            *line_size = 120;
        *lineptr = buffer;
    }
    else if (*line_size < a)
    {
        if (a > 120)
            *line_size = a;
        else
            *line_size = 120;
        *lineptr = buffer;
    }
    else
    {
        _strcpy(*lineptr, buffer);
        free(buffer);
    }
}
/**
 * _getline - gets input from input stream
 * @lineptr: A buffer to store the input from stream
 * @line_size: The size of lineptr
 * @stream: The stream to read from
 * Return: Number of bytes read
*/
ssize_t _getline(char **lineptr, size_t *line_size, FILE *stream)
{
    static ssize_t input_strm;
    ssize_t ret_val;
    char c = 'x', *buffer;
    int retn;

    if (input_strm == 0)
        fflush(stream);
    else 
        return (-1);
    input_strm = 0;
    
    buffer = malloc(sizeof(char) * 120);
    if (!buffer)
        return (-1);

    while (c != '\n')
    {
        retn = read(STDIN_FILENO, &c, 1);
        if (retn == -1 || (retn == 0 && input_strm == 0))
        {
            free(buffer);
            return (-1);
        }
        if (retn == 0 && input_strm != 0)
        {
            input_strm++;
            break;
        }
        if (input_strm >= 120)
            buffer = _realloc(buffer, input_strm, input_strm + 1);

        buffer[input_strm] = c;
        input_strm++;
    }
    buffer[input_strm] = '\0';

    reassign_lineptr(lineptr, line_size, buffer, input_strm);

    ret_val = input_strm;
    if (retn != 0)
        input_strm = 0;
    return (ret_val);
}