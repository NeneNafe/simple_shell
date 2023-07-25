#include "shell.h"

/**
 * list_len - Determines length of linked list.
 * @h: Pointer to first node.
 *
 * Return: Size of list.
 */

size_t list_len(const list_t *h)
{
	size_t j = 0;

	while (h)
	{
		h = h->next;
		j++;
	}
	return (j);
}

/**
 * list_to_strings - Returns an array of strings of the list->str.
 * @head: Pointer to first node.
 *
 * Return: Array of strings.
 */

char **list_to_strings(list_t *head)
{
	list_t *node = head;
	size_t i = list_len(head), j;
	char **strs;
	char *s;

	if (!head || !i)
		return (NULL);
	strs = malloc(sizeof(char *) * (i + 1));
	if (!strs)
		return (NULL);
	for (i = 0; node; node = node->next, i++)
	{
		s = malloc(_strlen(node->str) + 1);

		if (!s)
		{
			for (j = 0; j < i; j++)
				free(strs[j]);
			free(strs);
			return (NULL);
		}

		s = _strcpy(s, node->str);
		strs[i] = s;
	}
	strs[i] = NULL;
	return (strs);
}

/**
 * printlist - Prints all elements of a list_t linked list.
 * @h: Pointer to the first node.
 *
 * Return: Size of list.
 */

size_t printlist(const list_t *h)
{
	size_t j = 0;

	while (h)
	{
		_puts(convert_num(h->num, 10, 0));
		_putchar(':');
		_putchar(' ');
		_puts(h->str ? h->str : "(nil)");
		_puts("\n");
		h = h->next;
		j++;
	}
	return (j);
}

/**
 * node_start - Returns node whose string starts with prefix.
 * @node: Pointer to the list head.
 * @prefix: String to match.
 * @c: The next character after prefix to match.
 *
 * Return: Match node or NULL.
 */

list_t *node_start(list_t *node, char *prefix, char c)
{
	char *ptr = NULL;

	while (node)
	{
		ptr = starts_with(node->str, prefix);

		if (ptr && ((c == -1) || (*ptr == c)))
			return (node);
		node = node->next;
	}
	return (NULL);
}

/**
 * get_node - Gets the index of  a node.
 * @head: Pointer to list head.
 * @node: Pointer to the node.
 *
 * Return: Index of node or -1.
 */

ssize_t get_node(list_t *head, list_t *node)
{
	size_t j = 0;

	while (head)
	{
		if (head == node)
			return (j);
		head = head->next;
		j++;
	}
	return (-1);
}
