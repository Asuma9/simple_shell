#include "shell.h"

/**
 * create_full_path - Creates a full path from a directory and a command
 * @dir: The directory
 * @command: The command
 *
 * Return: A pointer to the full path
 */

char *create_full_path(const char *dir, const char *command)
{
	char *full_path = malloc(strlen(dir) + strlen(command) + 2);
	char *ptr = full_path;

	while (*dir)
	{
		*ptr++ = *dir++;
	}

	*ptr++ = '/';

	while (*command)
	{
		*ptr++ = *command++;
	}
	*ptr = '\0';
	return (full_path);
}

/**
 * custom_strdup - Duplicates a string
 * @src: The source string to duplicate
 *
 * Return: A pointer to the duplicated string
 */
char *custom_strdup(const char *src)
{
	char *dup = malloc(strlen(src) + 1);

	if (dup)
	{
		char *ptr = dup;

		while ((*ptr++ = *src++))
			;
	}
	return (dup);
}

/**
 * find_command_in_path - Finds a command in the PATH
 * @command: The command to find
 *
 * Return: A pointer to the command if found, NULL otherwise
 */

char *find_command_in_path(char *command)
{
	char *PATH;
	char *path_copy;
	char **path_directories;
	int idx;

	if (!command || strchr(command, '/'))/* If "/", consider it a path */
	{
		if (access(command, F_OK) == 0)/*Check command path exists */
			return (custom_strdup(command));
		else
			return (NULL);
	}
	PATH = getenv("PATH");
	/* Adding this PATH check after an error */
	if (!PATH)
	{
		return (NULL);/* Handle case where PATH is not set */
	}
	path_copy = custom_strdup(PATH);
	path_directories = tokenize_input(path_copy, ":");
	idx = 0;
	while (path_directories[idx])
	{
		char *full_path = create_full_path(path_directories[idx],
				command);

		struct stat st;

		if (stat(full_path, &st) == 0 && (st.st_mode & S_IXUSR))
		{
			free_tokenized_array(path_directories);
			free(path_copy);
			return (full_path);
		}
		free(full_path);
		idx++;
	}
	free_tokenized_array(path_directories);
	free(path_copy);
	return (NULL);
}
/**
 * free_tokenized_array - Frees a tokenized array.
 * @array: The tokenized array.
 */
void free_tokenized_array(char **array)
{
	if (!array)
		return;
	free(array);

}
