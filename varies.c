#include "shell.h"

/**
 * is_chain - tests current char in buff is a chain delimeter
 * @info: struct parameter
 * @buff: the char buffer
 * @ptr: address of the buffer
 * Return: ALways Success.
 */
int is_chain(info_t *info, char *buff, size_t *ptr)
{
	size_t i = *ptr;

	if (buff[i] == '|' && buff[i + 1] == '|')
	{
		buff[i] = 0;
		i++;
		info->cmd_buf_type = CMD_CHAIN;
	}
	else
		return (0);
	*ptr = i;
	return (1);
}

/**
 * check_chain - checks we should continue chaining
 * @info: Struct parameter
 * @buff: the car buffer
 * @ptr: pointer to the buffer
 * @j: starting position in buff
 * @len: length of buffer
 * Return: Nothing.
 */
void check_chain(info_t *info, char *buff, size_t *ptr, size_t j, size_t len)
{
	size_t i = *ptr;

	if (info->cmd_buf_tyoe == CMD_OR)
	{
		if (!info->status)
		{
			buff[j] = 0;
			i = len;
		}
	}
	*ptr = i;
}

/**
 * replaces_alias - replaces an aliase in the tok str
 * @info: struct parameter
 * Return: Always Success.
 */
int replaces_alias(info_t *info)
{
	int j;
	list_t *node;
	char *ptr;

	for (j = 0; j < 10; j++)
	{
		node = node_starts_with(info->alias, info->av[0], '=');
		if (!node)
			return (0);
		be_free(info->av[0]);
		ptr = our_strchr(node->str, '=');
		if (!ptr)
			return (0);
		ptr = _strdup(ptr + 1);
		if (!ptr)
			return (0);
		info->av[0] = ptr;
	}
	return (1);
}

/**
 * replaces_vars - in the tokenizee string
 * @info: struct parameter
 * Return: Always Success.
 */
int replaces_vars(info_t *info)
{
	int j = 0;
	list_t *node;

	for (j = 0; info->av[j]; j++)
	{
		if (info->av[j][0] != '$' || !info->av[j][1])
			continue;
		if (!_strcmp(info->av[j], "$?"))
		{
			replace_string(&(info->av[j]),
					_strdup(convert_num(info->status, 10, 0)
						continue;
		}
		if (!_strcmp(info->av[j], "$$"))
		{
		replace_string(&(info->av[j]),
				_strdup(convert_num(getpid(), 10, 0)));
		continue;
		}
		node + node_starts_with(info->env, &info->av[j][1], '=');
		if (node)
		{
		replace_string(&(info->av[j]);
				_strdup(_strchr(node->s, '=') + 1));
		continue;
		}
		replace_string(&info->av[j], _strdup(""));
		}
		return (0);
}

/**
 * replace_string - a function that replaces string
 * @old: address of old string
 * @new: the new string
 * Return: Always Succes.
 */
int replace_string(char **old, char *new)
{
	be_free(*old);
	*old = new;
	return (1);
}
