#include "shell.h"

/**
 * _myexit - exits the shell
 * @info: info structure address (ptr to). Used to maintain
 *        constant function prototype
 *  Return: exits with a given exit status
 *         (0) if info.argv[0] != "exit"
 */
int _myexit(info_t *info)
{
	int exit_check;

	if (info->argv[1])  /* If there is an exit arguement */
	{
		exit_check = _erratoi(info->argv[1]);
		if (exit_check == -1)
		{
			info->status = 2;
			print_error(info, "Illegal number: ");
			_eputs(info->argv[1]);
			_eputchar('\n');
			return (1);
		}
		info->err_num = _erratoi(info->argv[1]);
		return (-2);
	}
	info->err_num = -1;
	return (-2);
}

/**
 * _mycd - changes the current directory
 * @info: info structure address (ptr to). Used to maintain
 *        constant function prototype.
 *  Return: 0 always
 */
int _mycd(info_t *info)
{
	char *str, *dir, buff[1024];
	int chdir_ret;

	str = getcwd(buff, 1024);
	if (!str)
		_puts("TODO: >>getcwd failure message here<<\n");
	if (!info->argv[1])
	{
		dir = _getenv(info, "HOME=");
		if (!dir)
			chdir_ret =
				chdir((dir = _getenv(info, "PWD=")) ? dir : "/");
		else
			chdir_ret = chdir(dir);
	}
	else if (_strcmp(info->argv[1], "-") == 0)
	{
		if (!_getenv(info, "OLDPWD="))
		{
			_puts(str);
			_putchar('\n');
			return (1);
		}
		_puts(_getenv(info, "OLDPWD=")), _putchar('\n');
		chdir_ret =
			chdir((dir = _getenv(info, "OLDPWD=")) ? dir : "/");
	}
	else
		chdir_ret = chdir(info->argv[1]);
	if (chdir_ret == -1)
	{
		print_error(info, "can't cd to ");
		_eputs(info->argv[1]), _eputchar('\n');
	}
	else
	{
		_setenv(info, "OLDPWD", _getenv(info, "PWD="));
		_setenv(info, "PWD", getcwd(buff, 1024));
	}
	return (0);
}

/**
 * _myhelp - changes the current directory
 * @info: info structure address (ptr to). Used to maintain
 *        constant function prototype
 *  Return: Always 0
 */
int _myhelp(info_t *info)
{
	char **ag_array;

	ag_array = info->argv;
	_puts("help call executes. Function not yet implemented \n");
	if (0)
		_puts(*ag_array);
	return (0);
}
