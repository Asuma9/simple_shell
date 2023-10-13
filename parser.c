#include "shell.h"

/**
 * is_exec - determines if a file is an executable command
 * @info: info structure address (ptr to). Used to maintain
 *        constant function prototype
 * @path: pointer path to the file to check
 *
 * Return: 1 if true, 0 otherwise
 */
int is_exec(info_t *info, char *path)
{
	struct stat st;

	(void)info;
	if (!path || stat(path, &st))
		return (0);

	if (S_ISREG(st.st_mode) && (st.st_mode & S_IXUSR))
	{
		return (1);
	}
	return (0);
}

/**
 * dup_chars - duplicates characters
 * @path_str: pointer to the PATH string
 * @start: starting index
 * @stop: stopping index
 *
 * Return: pointer to new buffer
 */
char *dup_chars(char *path_str, int start, int stop)
{
	static char buff[1024];
	int i = 0, k = 0;

	for (k = 0, i = start; i < stop; i++)
		if (path_str[i] != ':')
			buff[k++] = path_str[i];
	buff[k] = 0;
	return (buff);
}

/**
 * find_path - finds this cmd in the PATH string
 * @info: info structure address (ptr to). Used to maintain
 *        constant function prototype
 * @path_str: pointer to the PATH string
 * @cmd: the cmd to find in PATH string
 *
 * Return: full path of cmd if found or NULL
 */
char *find_path(info_t *info, char *path_str, char *cmd)
{
	int i = 0, curr_pos = 0;
	char *path;

	if (!path_str)
		return (NULL);
	if ((_strlen(cmd) > 2) && starts_with(cmd, "./"))
	{
		if (is_exec(info, cmd))
			return (cmd);
	}
	while (1)
	{
		if (!path_str[i] || path_str[i] == ':')
		{
			path = dup_chars(path_str, curr_pos, i);
			if (!*path)
				_strcat(path, cmd);
			else
			{
				_strcat(path, "/");
				_strcat(path, cmd);
			}
			if (is_exec(info, path))
				return (path);
			if (!path_str[i])
				break;
			curr_pos = i;
		}
		i++;
	}
	return (NULL);
}
