#include "shell.h"

/**
 * get_environ - returns the string array copy of our environ
 * @info: info structure address (ptr to). Used to maintain
 *        constant function prototype.
 * Return: Always 0
 */
char **get_environ(info_t *info)
{
	if (!info->environ || info->env_changed)
	{
		info->environ = list_to_strings(info->env);
		info->env_changed = 0;
	}

	return (info->environ);
}

/**
 * _unsetenv - Removes an environment variable
 * @info: info structure address (ptr to). Used to maintain
 *        constant function prototype.
 * @var: the string env var property
 * Return: 1 on successful removal, 0 otherwise
 */
int _unsetenv(info_t *info, char *var)
{
	char *ptr;
	list_t *node = info->env;
	size_t i = 0;

	if (!node || !var)
		return (0);

	while (node)
	{
		ptr = starts_with(node->str, var);
		if (ptr && *ptr == '=')
		{
			info->env_changed = delete_node_n(&(info->env), i);
			i = 0;
			node = info->env;
			continue;
		}
		node = node->next;
		i++;
	}
	return (info->env_changed);
}

/**
 * _setenv - Initializes a new environment variable,
 *             or modifies an existing one
 * @info: info structure address (ptr to). Used to maintain
 *        constant function prototype.
 * @var_prop: the string environ variable property
 * @value: the string environ variable value
 *  Return: Always 0
 */
int _setenv(info_t *info, char *var_prop, char *value)
{
	char *buff = NULL;
	char *ptr;
	list_t *node;

	if (!var_prop || !value)
		return (0);

	buff = malloc(_strlen(var_prop) + _strlen(value) + 2);
	if (!buff)
		return (1);
	_strcpy(buff, var_prop);
	_strcat(buff, "=");
	_strcat(buff, value);
	node = info->env;
	while (node)
	{
		ptr = starts_with(node->str, var_prop);
		if (ptr && *ptr == '=')
		{
			free(node->str);
			node->str = buff;
			info->env_changed = 1;
			return (0);
		}
		node = node->next;
	}
	add_node_tail(&(info->env), buff, 0);
	free(buff);
	info->env_changed = 1;
	return (0);
}
