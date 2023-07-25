#include "shell.h"

/**
 * clear_info - initializes struct info
 * @info: struct address
 */
void clear_info(info_t *info)
{
	info->arg = NULL;
	info->av = NULL;
	info->path = NULL;
	info->ac = 0;
}

/**
 * set_info - initializes struct info
 * @info: the struct address
 * @av: argument vector:
 * Return: Nothing
 */
void set_info(info_t *info, char **av)
{
	int j = 0;

	info->fname = av[0];
	if (info->arg)
	{
		info->av = strtow(info->arg, " \t");
		if (!info->av)
		{
			info->av = malloc(sizeof(char *) * 2);
			if (info->av)
			{
				info->av[0] = _strdup(info->arg);
				info->av[1] = NULL;
			}
		}
		for (j = 0; info->av && info->av[j]; j++)
			;
		info->ac = j;

		replaces_alias(info);
		replaces_vars(info);
	}
}

/**
 * free_info - frees struct info fields
 * @info: struct address
 * @all: becomes true if freeing all fields
 */
void free_info(info_t *info, int all)
{
	free_str(info->av);
	info->av = NULL;
	info->path = NULL;
	if (all)
	{
		if (!info->cmd_buf)
			free(info->arg);
		if (info->env)
			free_list(&(info->env));
		if (info->his)
			free_list(&(info->his));
		if (info->alias)
			free_list(&(info->alias));
		free_str(info->environ);
		info->environ = NULL;
		be_free((void **)info->cmd_buf);
		if (info->readfd > 2)
			close(info->readfd);
		_putchar(BUF_FLUSH);
	}
}
