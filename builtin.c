#include "shell.h"

/**
 * our_exit - thr program exits the shell
 * @info: Struct info containing all potential args
 * Return: on success (exit)
 */
int our_exit(info_t *info)
{
	int checker;

	if (info->av[1]) /* where there is an exit argument */
	{
		checker = our_erratoi(info->av[1]);
		if (checker == -1)
		{
			info->status = 2;
			print_errs(info, "Unknown Number: ");
			_nputs(info->av[1]);
			_cputchar('\n');
			return (1);
		}
		info->err_num = our_erratoi(info->av[1]);
		return (-2);
	}
	info->err_num = -1;
	return (-2);
}

/**
 * our_cd - changes the current working directory
 * @info: Struct info containing all potential args
 * Return: Success.
 */
int our_cd(info_t *info)
{
	char *str, *dir, buffer[1024];
	int chld_dir;

	str = getcwd(buffer, 1024);
	if (!str)
		_nputs("TODO: >>getcwd failure emsg here<<\n");
	if (!info->av[1])
	{
		dir = our_getenv(info, "HOME=");
		if (!dir)
			chld_dir = /* TODO: what should this be? */
			       chdir((dir = our_getenv(info, "PWD=")) ? dir : "/");
		else
		chld_dir = chdir(dir);
	}
	else if (_strcmp(info->av[1], "-") == 0)
	{
		if (!our_getenv(info, "OLDPWD="))
		{
			_puts(str);
			_cputchar('\n');
			return (1);
		}
		_puts(our_getenv(info, "OLDPWD=")), _cputchar('\n');
		chld_dir = /* TODO: what should this be? */
			chdir((dir = our_getenv(info, "OLDPWD=")) ? dir : "/");
	}
	else
		chld_dir = chdir(info->av[1]);
	if (chld_dir == -1)
	{
		print_errs(info, "cannot cd to ");
		_nputs(info->av[1]), _cputchar('\n');
	}
	else
	{
		_setenv(info, "OLDPWD", our_getenv(info, "PWD="));
		_setenv(info, "PWD", getcwd(buffer, 1024));
	}
	return (0);
}

/**
 * _ourhelp - changes the pwd fo the process
 * @info: Struct info
 * Return: Success.
 */
int _ourhelp(info_t *info)
{
	char **args;

	args = info->av;
	_puts("help call works. Function not yet implemented \n");
	if (0)
		_puts(*args);
	return (0);
}
