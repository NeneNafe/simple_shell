#include "shell.h"

/**
 * our_hist - displays the history list
 * @info: struct containing all the parameters
 * Return: Always Success.
 */
int our_hist(info_t *info)
{
	printlist(info->his);
	return (0);
}

/**
 * sets_alias - a function that sets alias to string
 * @info: Struct containing all the parameters
 * @s: stirng alias to be used
 * Return: Success 0, 1 on error.
 */
int sets_alias(info_t *info, char *s)
{
	char *ptr;

	ptr = our_strchr(s, '=');
	if (!ptr)
		return (1);
	if (!*++ptr)
		return (our_alias(info, s));
	our_alias(info, s);
	return (add_node_end(&(info->alias), s, 0) == NULL);
}

/**
 * our_alias - unsets alias to string
 * @info: struct parameter
 * @s: the stirng alias
 * Return: Always success.
 */
int our_alias(info_t *info, char *s)
{
	char *ptr, x;
	int ret;

	ptr = our_strchr(s, '=');
	if (!ptr)
		return (1);
	x = *ptr;
	*ptr = 0;
	ret = delete_node(&(info->alias),
		get_node(info->alias, node_start(info->alias, s, -1)));
	*ptr = x;
	return (ret);
}

/**
 * prints_alias - prints an alias string
 * @node: the alias node
 * Return: on Success 0, otherwise 1
 */
int prints_alias(list_t *node)
{
	char *ptr = NULL, *j = NULL;

	if (node)
	{
		ptr = our_strchr(node->str, '=');
		for (j = node->str; j <= ptr; j++)
			_cputchar(*j);
		_cputchar('\'');
		_puts(ptr + 1);
		_puts("'\n");
		return (0);
	}
	return (1);
}

/**
 * mim_alias - mimics the alias builtin function
 * @info: Struct containg all parameters
 * Return: Always Success.
 */
int mim_alias(info_t *info)
{
	int m = 0;
	char *ptr = NULL;
	list_t *node = NULL;

	if (info->ac == 1)
	{
		node = info->alias;
		while (node)
		{
			prints_alias(node);
			node = node->next;
		}
		return (0);
	}
	for (m = 1; info->av[m]; m++)
	{
		ptr = our_strchr(info->av[m], '=');
		if (ptr)
			sets_alias(info, info->av[m]);
		else
			prints_alias(node_start(info->alias, info->av[m], '='));
	}
	return (0);
}
