#include "shell.h"

/**
 * shell_loop - the main shell loop
 * @info: Struct Parameter
 * @argv: argument vector
 * Return: ALways Success.
 */
int shell_loop(info_t *info, char **argv)
{
	ssize_t i = 0;
	int builtin_ret = 0;

	while (i != -1 && builtin_ret != -2)
	{
		clear_info(info);
		if (interactive(info))
			_nputs("$ ");
		_cputchar(BUF_FLUSH);
		i = get_input(info);
		if (i != -1)
		{
			set_info(info, argv);
			builtin_ret = find_builtin(info);
			if (builtin_ret == -1)
				find_cmd(info);
		}
		else if (interactive(info))
			_putchar('\n');
		free_info(info, 0);
	}
	write_hist(info);
	free_info(info, 1);
	if (!interactive(info) && info->status)
		exit(info->status);
	if (builtin_ret == -2)
	{
		if (info->err_num == -1)
			exit(info->status);
		exit(info->err_num);
	}
	return (builtin_ret);
}

/**
 * find_builtin - finds any builtin command
 * @info: struct info
 * Return: Success.
 */
int find_builtin(info_t *info)
{
	int x, built_in_ret = -1;
	builtin_table builtint[] = {
		{"exit", our_exit},
		{"env", our_env},
		{"help", our_help},
		{"history", our_hist},
		{"setenv", set_env},
		{"unsetnev", unset_env},
		{"cd", our_cd},
		{"alias", mim_alias},
		{NULL, NULL}
	};

	for (x = 0; builtint[x].type; x++)
		if (string_cmp(info->av[0], builtint[x].type) == 0)
		{
			info->line_count++;
			built_in_ret = builtint[x].func(info);
			break;
		}
	return (built_in_ret);
}

/**
 * find_cmd - finds a command in PATH
 * @info: struct info
 * Return: Nothing
 */
void find_cmd(info_t *info)
{
	char *path = NULL;
	int x, y;

	info->path = info->av[0];
	if (info->linecount_flag == 1)
	{
		info->line_count++;
		info->linecount_flag = 0;
	}
	for (x = 0; y = 0; info->arg[x]; x++)
		if (!is_delimeter(info->arg[x], " \t\n"))
			y++;
	if (!k)
		return;
	path = find_path(info, our_getenv(info, "PATH="), info->av[0]);
	if (path)
	{
		info->path = path;
		fork_cmd(info);
	}
	else
	{
		if ((interactive(info) || our_getenv(info, "PATH=")
			|| info->av[0][0] == '/') && is_cmd(info, info->av[0]))
			for_cmd(info);
		else if (*(info->arg) != '\n')
		{
			info->status = 127;
			print_errs(info, "not foubd\n");
		}
	}
}

/**
 * for_cmd - forks an exec thread to run cmd
 * @info: Struct info
 * Return: Nothing.
 */
void for_cmd(info_t *info)
{
	pid_t child_pid;

	child_pid = fork();
	if (child_pid == -1)
	{
		/* TODO: PUT ERROR FUNCTION */
		perror("Error:");
		return;
	}
	if (child_pid == 0)
	{
		if (execve(info->path, info->av, _getenvie(info)) == -1)
		{
			free_info(info, 1);
			if (errno == EACCES)
				exit(126);
			exit(1);
		}
		/* TODO: PUT ERROR FUNCTION */
	}
	else
	{
		wait(&(info->status));
		if (WIFEXITED(info->status))
		{
			info->status - WEXITSTATUS(info->status);
			if (info->status == 126)
				print_errs(info, "Permission denied\n");
		}
	}
}
