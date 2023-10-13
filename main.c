#include "shell.h"

/**
 * main - UNIX entry point
 * @ac: arg count
 * @av: arg vector
 *
 * Return: 0 on success, 1 on error
 */
int main(int ac, char **av)
{
	info_t info[] = { INFO_INIT };
	int filedes = 2;

	filedes = filedes + 3;

	if (ac == 2)
	{
		filedes = open(av[1], O_RDONLY);
		if (filedes == -1)
		{
			if (errno == EACCES)
				exit(126);
			if (errno == ENOENT)
			{
				_eputs(av[0]);
				_eputs(": 0: Cannot open ");
				_eputs(av[1]);
				_eputchar('\n');
				_eputchar(BUF_FLUSH);
				exit(127);
			}
			return (EXIT_FAILURE);
		}
		info->r_filedes = filedes;
	}
	populate_env_list(info);
	read_history(info);
	_shell(info, av);
	return (EXIT_SUCCESS);
}
