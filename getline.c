#include "shell.h"

/**
 * input_handle - buffers series of chained commands thro automation
 * @info: info structure address (ptr to). Used to maintain
 *        constant function prototype
 * @buff: address of the buffer
 * @len: address of len variable
 *
 * Return: bytes read
 */
ssize_t input_handle(info_t *info, char **buff, size_t *len)
{
	ssize_t b_read = 0;
	size_t len_ptr = 0;

	if (!*len) /* if nothing left in the buffer, fill it */
	{
		/*free memory from previous allocation*/
		free(*buff);
		*buff = NULL;
		signal(SIGINT, sigintHandler); /* initiate a signal*/
#if USE_GETLINE
		b_read = getline(buf, &len_p, stdin); /* use standard getline*/
#else
		b_read = _getline(info, buff, &len_ptr); /* call customized one */
#endif
		if (b_read > 0)
		{
			if ((*buff)[b_read - 1] == '\n')
			{
				(*buff)[b_read - 1] = '\0'; /* remove trailing newline */
				b_read--;
			}
			info->linesize_flag = 1; /*set flag to 1*/
			remove_comments(*buff);
			build_hist_list(info, *buff, info->histcount++);
			/* if (_strchr(*buf, ';')) check if this is a command chain */
			{
				*len = b_read;
				info->cmd_buff = buff;
			}
		}
	}
	return (b_read);
}

/**
 * get_input - gets a line without the newline
 * @info: info structure address (ptr to). Used to maintain
 *        constant function prototype
 * Return: bytes read and stored in info
 */
ssize_t get_input(info_t *info)
{
	static size_t i, j, length;
	static char *buff; /* semiclon (;) command chain buffer */
	ssize_t b_read = 0;
	char **buf_p = &(info->arg), *ptr;

	_putchar(BUF_FLUSH);
	b_read = input_handle(info, &buff, &length);
	if (b_read == -1) /* EOF */
		return (-1);
	if (length)	/* we have commands left in the chain buffer */
	{
		j = i; /* init new iterator to current buf position */
		ptr = buff + i; /* get pointer for return */

		check_chain(info, buff, &j, i, length);
		while (j < length) /* iterate to semicolon or end */
		{
			if (is_chain(info, buff, &j))
				break;
			j++;
		}

		i = j + 1; /* increment past nulled ';'' */
		if (i >= length) /* reached end of buffer? */
		{
			i = length = 0; /* reset position and length */
			info->cmd_buf_type = CMD_NORM;
		}

		*buf_p = ptr; /* pass back pointer to current command position */
		return (_strlen(ptr)); /* return length of current command */
	}

	*buf_p = buff; /* else not a chain, pass back buffer from _getline() */
	return (b_read); /* return length of buffer from _getline() */
}

/**
 * read_buff - reads a buffer
 * @info: info structure address (ptr to). Used to maintain
 *        constant function prototype
 * @buff: pointer to buffer
 * @size: size of read bytes
 *
 * Return: bytes read
 */
ssize_t read_buff(info_t *info, char *buff, size_t *size)
{
	ssize_t bytes_read = 0;

	if (*size)
		return (0);
	bytes_read = read(info->r_filedes, buff, READ_BUF_SIZE);
	if (bytes_read >= 0)
		*size = bytes_read;
	return (bytes_read);
}

/**
 * _getline - gets the next line of input from STDIN
 * @info: info structure address (ptr to). Used to maintain
 *        constant function prototype
 * @ptr: address of pointer to buffer, preallocated or NULL
 * @length: size of preallocated ptr buffer if not NULL
 *
 * Return: size
 */
int _getline(info_t *info, char **ptr, size_t *length)
{
	static char buff[READ_BUF_SIZE];
	static size_t i, len;
	size_t k;
	ssize_t r = 0, size = 0;
	char *ptr_1 = NULL, *new_p = NULL, *ch;

	ptr_1 = *ptr;
	if (ptr_1 && length)
		size = *length;
	if (i == len)
		i = len = 0;

	r = read_buff(info, buff, &len);
	if (r == -1 || (r == 0 && len == 0))
		return (-1);

	ch = _strchr(buff + i, '\n');
	k = ch ? 1 + (unsigned int)(ch - buff) : len;
	new_p = _realloc(ptr_1, size, size ? size + k : k + 1);
	if (!new_p) /* if memory alloc fails */
		return (ptr_1 ? free(ptr_1), -1 : -1);

	if (size)
		_strncat(new_p, buff + i, k - i);
	else
		_strncpy(new_p, buff + i, k - i + 1);

	size += k - i;
	i = k;
	ptr_1 = new_p;

	if (length)
		*length = size;
	*ptr = ptr_1;
	return (size);
}

/**
 * sigintHandler - blocks ctrl-C
 * @sig_num: the signal number
 *
 * Return: void
 */
void sigintHandler(__attribute__((unused))int sig_num)
{
	_puts("\n");
	_puts("$ ");
	_putchar(BUF_FLUSH);
}
