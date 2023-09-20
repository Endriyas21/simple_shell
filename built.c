#include "shell.h"

/**
 * _exiter - exit from shell
 *
 * @info: Struct with potential arguments
 * constant fun protyp.
 *
 * Return: exit with given exit cmd
 * (0) if info.argv[0] != exit
 */

int _exiter(info_t *info)
{
	int exchecker;

	if (info->argv[1]) /* for an exit arg*/
	{
		exchecker = _erratoi(info->argv[1]);
		if (exchecker == -1)
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
 * _mydir - changes cmd
 * @info: Struct contains potential arg
 * constant fun proto.
 * Return: returns 0
 */

int _mydir(info_t *info)
{
	char *s, *dir, buffer[1024];
	int chdr_rt;

	s = getcwd(buffer, 1024);
	if (!s)
		_puts("TODO: >>getcwd failure message here <<\n");
	if (!info->argv[1])
	{
		dir = _getenv(info, "HOME=");
		if (!dir)
			chdr_rt = /* TODO: what could it be? */
				chdir((dir = _getenv(info, "PWD=")) ? dir : "/");
		else
			chdr_rt = chdir(dir);
	}
	else if (_strcmp(info->argv[1], "-") == 0)
	{
		if (!_getenv(info, "OLDPWD="))
		{
			_puts(s);
			_putchar('\n');
			return (1);
		}
		_puts(_getenv(info, "OLDPWD=")), _putchar('\n');
		chdr_rt = /* TODO: what should this be? */
			chdir((dir = _getenv(info, "OLDPWD=")) ? dir : "/");
	}
	else
		chdr_rt = chdir(info->argv[1]);
	if (chdr_rt == -1)
	{
		print_error(info, "can't cd to ");
		_eputs(info->argv[1]), _eputchar('\n');
	}
	else
	{
		_setenv(info, "OLDPWD", _getenv(info, "PWD="));
		_setenv(info, "PWD", getcwd(buffer, 1024));
	}
	return (0);
}

/**
 * _myhelp - changes cmd
 * @info: Struct with potential args
 * constant fun protyp.
 * Return: 0
 */
int _myhelp(info_t *info)
{
	char **arg_array;

	arg_array = info->argv;
	_puts("help call works as Fun isnot implemented \n");
	if (0)
		_puts(*arg_array); /* temP work_around */
	return (0);
}
