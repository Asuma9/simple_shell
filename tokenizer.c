#include "shell.h"

/**
 * **_strtow - splits a string into words. Repeat delimiters are ignored
 * @str: the input string
 * @delim: the string delimeter
 * Return: a pointer to an array of strings, or NULL on failure
 */

char **_strtow(char *str, char *delim)
{
	int i, j, k, m, numwords = 0;
	char **str_1;

	if (str == NULL || str[0] == 0)
		return (NULL);

	if (!delim)
		delim = " ";
	for (i = 0; str[i] != '\0'; i++)
		if (!is_delim(str[i], delim) && (is_delim(str[i + 1], delim) || !str[i + 1]))
			numwords++;

	if (numwords == 0)
		return (NULL);
	str_1 = malloc((1 + numwords) * sizeof(char *));
	if (!str_1)
		return (NULL);
	for (i = 0, j = 0; j < numwords; j++)
	{
		while (is_delim(str[i], delim))
			i++;
		k = 0;
		while (!is_delim(str[i + k], delim) && str[i + k])
			k++;
		str_1[j] = malloc((k + 1) * sizeof(char));
		if (!str_1[j])
		{
			for (k = 0; k < j; k++)
				free(str_1[k]);
			free(str_1);
			return (NULL);
		}
		for (m = 0; m < k; m++)
			str_1[j][m] = str[i++];
		str_1[j][m] = 0;
	}
	str_1[j] = NULL;
	return (str_1);
}

/**
 * **_strtow1 - splits a string into words
 * @str: the input string
 * @delim: string delimeter
 * Return: a pointer to an array of strings, or NULL on failure
 */
char **_strtow1(char *str, char delim)
{
	int i, j, k, m, numwords = 0;
	char **str_1;

	if (str == NULL || str[0] == 0)
		return (NULL);
	for (i = 0; str[i] != '\0'; i++)
		if ((str[i] != delim && str[i + 1] == delim) ||
		    (str[i] != delim && !str[i + 1]) || str[i + 1] == delim)
			numwords++;
	if (numwords == 0)
		return (NULL);
	str_1 = malloc((1 + numwords) * sizeof(char *));
	if (!str_1)
		return (NULL);
	for (i = 0, j = 0; j < numwords; j++)
	{
		while (str[i] == delim && str[i] != delim)
			i++;
		k = 0;
		while (str[i + k] != delim && str[i + k] && str[i + k] != delim)
			k++;
		str_1[j] = malloc((k + 1) * sizeof(char));
		if (!str_1[j])
		{
			for (k = 0; k < j; k++)
				free(str_1[k]);
			free(str_1);
			return (NULL);
		}
		for (m = 0; m < k; m++)
			str_1[j][m] = str[i++];
		str_1[j][m] = 0;
	}
	str_1[j] = NULL;
	return (str_1);
}
