#include "shell.h"

/**
 * get_hist_file - gets the history file
 * @info: info structure address (ptr to). Used to maintain
 *        constant function prototype
 * Return: allocated string containing history file
 */

char *get_hist_file(info_t *info)
{
	char *buffer, *dir;

	dir = _getenv(info, "HOME=");
	if (!dir)
		return (NULL);
	buffer = malloc(sizeof(char) * (_strlen(dir) + _strlen(HIST_FILE) + 2));
	if (!buffer)
		return (NULL);
	buffer[0] = 0;
	_strcpy(buffer, dir);
	_strcat(buffer, "/");
	_strcat(buffer, HIST_FILE);
	return (buffer);
}

/**
 * write_history - creates a file, or appends to an existing file
 * @info: info structure address (ptr to). Used to maintain
 *        constant function prototype
 * Return: 1 on success, else -1
 */
int write_history(info_t *info)
{
	ssize_t filedes;
	char *filename = get_hist_file(info);
	list_t *node = NULL;

	if (!filename)
		return (-1);

	filedes = open(filename, O_CREAT | O_TRUNC | O_RDWR, 0644);
	free(filename);
	if (filedes == -1)
		return (-1);
	for (node = info->history; node; node = node->next)
	{
		_putsfd(node->str, filedes);
		_putfd('\n', filedes);
	}
	_putfd(BUF_FLUSH, filedes);
	close(filedes);
	return (1);
}

/**
 * read_history - reads history from file
 * @info: info structure address (ptr to). Used to maintain
 *        constant function prototype
 * Return: histcount on success, 0 otherwise
 */
int read_history(info_t *info)
{
	int i, last = 0, linecount = 0;
	ssize_t filedes, rd_len, f_size = 0;
	struct stat st;
	char *buff = NULL, *filename = get_hist_file(info);

	if (!filename)
		return (0);

	filedes = open(filename, O_RDONLY);
	free(filename);
	if (filedes == -1)
		return (0);
	if (!fstat(filedes, &st))
		f_size = st.st_size;
	if (f_size < 2)
		return (0);
	buff = malloc(sizeof(char) * (f_size + 1));
	if (!buff)
		return (0);
	rd_len = read(filedes, buff, f_size);
	buff[f_size] = 0;
	if (rd_len <= 0)
		return (free(buff), 0);
	close(filedes);
	for (i = 0; i < f_size; i++)
		if (buff[i] == '\n')
		{
			buff[i] = 0;
			build_hist_list(info, buff + last, linecount++);
			last = i + 1;
		}
	if (last != i)
		build_hist_list(info, buff + last, linecount++);
	free(buff);
	info->histcount = linecount;
	while (info->histcount-- >= HIST_MAX)
		delete_node_n(&(info->history), 0);
	renumber_hist(info);
	return (info->histcount);
}

/**
 * build_hist_list - adds an entry to a history linked list
 * @info: info structure address (ptr to). Used to maintain
 *        constant function prototype
 * @buff: pointer buffer
 * @linecount: the history linecount, histcount
 *
 * Return: Always 0
 */
int build_hist_list(info_t *info, char *buff, int linecount)
{
	list_t *node = NULL;

	if (info->history)
		node = info->history;
	add_node_tail(&node, buff, linecount);

	if (!info->history)
		info->history = node;
	return (0);
}

/**
 * renumber_hist - renumbers the history linked list after changes
 * @info: info structure address (ptr to). Used to maintain
 *        constant function prototype
 * Return: the new histcount
 */
int renumber_hist(info_t *info)
{
	list_t *node = info->history;
	int i = 0;

	while (node)
	{
		node->num = i++;
		node = node->next;
	}
	return (info->histcount = i);
}
