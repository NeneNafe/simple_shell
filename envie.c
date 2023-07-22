#include "shell.h"

/**
 * our_env - prints the current working environment
 * @info: Struct containing possible parameters
 * Return: Always Success
 */
int our_env(info_t *info)
{
	our_list_str(info->env);
	return (0);
}

/**
 * our_getenv - prints the value of an env var
 * @info: Struct info containing parameters
 * @name: environ name
 * Return: Success.
 */
char *our_getenv(info_t *info, const char *name)
{
	list_t *node = info->env;
	char *ptr;

	while (node)
	{
		ptr = starts_with(node->s, name);
		if (ptr && *ptr)
			return (ptr);
		node = node->next;
	}
	return (NULL);
}

/**
 * our_setenv - modifies an existing env
 * @info: Struct Parameters
 * Return: Always Success.
 */
int our_setenv(info_t *info)
{
	if (info->ac != 3)
	{
		_nputs("Incorrect number of arguments\n");
		return (1);
	}
	if (set_env(info, info->av[1], info->av[2]))
		return (0);
	return (1);
}

/**
 * unset_env - removes an environment variable
 * @info: Struct Parameters
 * Return: Always Success.
 */
int unset_env(info_t *info)
{
	int j;

	if (info->av == 1)
	{
		_nputs("Too few arguments.\n");
		return (1);
	}
	for (j = 1; j <= info->ac; j++)
		our_unsetenv(info, info->av[j]);
	return (0);
}

/**
 * pop_env_list - populate env linked list
 * @info: Struct info parameters
 * Return: Always Success.
 */
int pop_env_list(info_t *info)
{
	list_t *node = NULL;
	size_t a;

	for (a = 0; environ[a]; a++)
		add_node_end(&node, environ[a], 0);
	info->env = node;
	return (0);
}
