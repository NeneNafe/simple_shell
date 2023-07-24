#include "shell.h"

/**
 * _getenvie - return a string arr copy of the environ
 * @info: struct info
 * Return: Always Success.
 */
char **_getenvie(info_t *info)
{
	if (!info->environ || info->envi_chngd)
	{
		info->environ - list_to_strings(info->env);
		info->envi_chngd = 0;
	}

	return (info->environ);
}

/**
 * our_unsetenv - Removes an environment var
 * @info: Struct info
 * @var: var property
 * Return: 1 on delete, 0 otherwise
 */
int our_unsetenv(info_t *info, char *var)
{
	list_t *node = info->env;
	size_t j = 0;
	char *ptr;

	if (!node || !var)
		return (0);
	while (node)
	{
		p = starts_with(node->str, var);
		if (ptr && *ptr == '=')
		{
			info->envi_chngd = delete_node_at_index(&(info->env), j);
			j = 0;
			node = info->env;
			continue;
		}
		node = node->next;
		j++;
	}
	return (info->env_chngd);
}

/**
 * our_setenv - initializes a news environ var
 * @info: Struct info
 * @var: the str envi var property
 * @value: the variable value
 * Return: Always 0.
 */
int _setenv(info_t *info, char *var, char *value)
{
	char *buff = NULL;
	list_t *node;
	char *ptr;

	if (!var || !value)
		return (0);
	buff = malloc(_strlen(var) + _strlen(value) + 2);
	if (!buff)
		return (1);
	_strcpy(buff, var);
	_strcat(buff, "=");
	_strcat(buff, value);
	node = info->env;
	while (node)
	{
		ptr = starts_with(node->s, var);
		if (ptr && *ptr == '=')
		{
			free(node->s);
			node->s = buff;
			info->envi_chngd = 1;
			return (0);
		}
		node = node->next;
	}
	add_node_end(&(info->env), buff, 0);
	free(buff);
	info->envi_chngd = 1;
	return (0);
}
