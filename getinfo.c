#include "shell.h"

/**
 * clear_info - clears & initializes info_t struct
 * @info: info structure address (ptr to)
 */
void clear_info(info_t *info)
{
	info->argc = 0;
	info->arg = NULL;
	info->argv = NULL;
	info->path = NULL;
}

/**
 * set_info - initializes info_t struct
 * @info: info structure address (ptr to)
 * @arg_v: argument vector
 */
void set_info(info_t *info, char **arg_v)
{
	int j = 0;

	info->fname = arg_v[0];
	if (info->arg)
	{
		info->argv = _strtow(info->arg, " \t");
		if (!info->argv)
		{

			info->argv = malloc(sizeof(char *) * 2);
			if (info->argv)
			{
				info->argv[0] = _strdup(info->arg);
				info->argv[1] = NULL;
			}
		}
		for (j = 0; info->argv && info->argv[j]; j++)
			;
		info->argc = j;

		replace_alias(info);
		replace_vars(info);
	}
}

/**
 * free_info - frees info_t struct fields after execution
 * @info: info structure address (ptr to)
 * @all_fields: true if able to free all fields
 */
void free_info(info_t *info, int all_fields)
{
	free_argv(info->argv);
	info->argv = NULL;
	info->path = NULL;
	if (all_fields)
	{
		if (!info->cmd_buff)
			free(info->arg);
		if (info->env)
			free_list(&(info->env));
		if (info->history)
			free_list(&(info->history));
		if (info->alias)
			free_list(&(info->alias));
		free_argv(info->environ);
			info->environ = NULL;
		free_buff((void **)info->cmd_buff);
		if (info->r_filedes > 2)
			close(info->r_filedes);
		_putchar(BUF_FLUSH);
	}
}
