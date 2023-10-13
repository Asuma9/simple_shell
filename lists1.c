#include "shell.h"

/**
 * list_len - determines length of linked list
 * @head: pointer to first node
 *
 * Return: size of list
 */
size_t list_len(const list_t *head)
{
	size_t i = 0;

	while (head)
	{
		head = head->next;
		i++;
	}
	return (i);
}

/**
 * list_to_strings - returns an array of strings of the list->str
 * @head: pointer to first node
 *
 * Return: array of strings
 */
char **list_to_strings(list_t *head)
{
	list_t *node = head;
	size_t i = list_len(head), j;
	char **temp_str;
	char *nex_str;

	if (!head || !i)
		return (NULL);
	temp_str = malloc(sizeof(char *) * (i + 1));
	if (!temp_str)
		return (NULL);
	for (i = 0; node; node = node->next, i++)
	{
		nex_str = malloc(_strlen(node->str) + 1);
		if (!nex_str)
		{
			for (j = 0; j < i; j++)
				free(temp_str[j]);
			free(temp_str);
			return (NULL);
		}

		nex_str = _strcpy(nex_str, node->str);
		temp_str[i] = nex_str;
	}
	temp_str[i] = NULL;
	return (temp_str);
}

/**
 * print_list - prints all elements of a list_t linked list
 * @head: pointer to first node
 *
 * Return: size of list
 */
size_t print_list(const list_t *head)
{
	size_t i = 0;

	while (head)
	{
		_puts(convert_num(head->num, 10, 0));
		_putchar(':');
		_putchar(' ');
		_puts(head->str ? head->str : "(nil)");
		_puts("\n");
		head = head->next;
		i++;
	}
	return (i);
}

/**
 * node_starts_with - returns node whose string starts with prefix
 * @head: pointer to list head
 * @prefix: string to match
 * @c: the next character after prefix to match
 *
 * Return: match node or null
 */
list_t *node_starts_with(list_t *head, char *prefix, char c)
{
	char *ptr = NULL;

	while (head)
	{
		ptr = starts_with(head->str, prefix);
		if (ptr && ((c == -1) || (*ptr == c)))
			return (head);
		head = head->next;
	}
	return (NULL);
}

/**
 * get_node_index - gets the index of a node
 * @head: pointer to first node of list
 * @node: pointer to the node
 *
 * Return: index of node or -1
 */
ssize_t get_node_index(list_t *head, list_t *node)
{
	size_t i = 0;

	while (head)
	{
		if (head == node)
			return (i);
		head = head->next;
		i++;
	}
	return (-1);
}
