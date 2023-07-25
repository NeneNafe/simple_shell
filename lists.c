#include "shell.h"

/**
 * add_node - Adds a node to the start of the list.
 * @head: Address of pointer to head node.
 * @str: Str field of node.
 * @num: Node index used by history
 *
 * Return: Size of list.
 */

list_t *add_node(list_t **head, const char *str, int num)
{
	list_t *new_head;

	if (!head)
		return (NULL);
	new_head = malloc(sizeof(list_t));
	if (!new_head)
		return (NULL);
	our_memset((void *)new_head, 0, sizeof(list_t));
	new_head->num = num;
	if (str)
	{
		new_head->str = _strdup(str);
		if (!new_head->str)
		{
			free(new_head);
			return (NULL);
		}
	}
	new_head->next = *head;
	*head = new_head;
	return (new_head);
}

/**
 * add_node_end - Adds a node to the end of the list.
 * @head: Address of pointer to head node.
 * @s: String field of node.
 * @num: Node index used by history.
 * Return: Size of list
 */

list_t *add_node_end(list_t **head, const char *s, int num)
{
	list_t *new_node, *node;

	if (!head)
		return (NULL);

	node = *head;
	new_node = malloc(sizeof(list_t));
	if (!new_node)
		return (NULL);
	our_memset((void *)new_node, 0, sizeof(list_t));
	new_node->num = num;
	if (s)
	{
		new_node->str = _strdup(s);
		if (!new_node->str)
		{
			free(new_node);
			return (NULL);
		}
	}
	if (node)
	{
		while (node->next)
			node = node->next;
		node->next = new_node;
	}
	else
		*head = new_node;
	return (new_node);
}

/**
 * our_list_str - Prints only the str element of a list_t linked list.
 * @h: Pointer to first node.
 *
 * Return: Size of list.
 */

size_t our_list_str(const list_t *h)
{
	size_t j = 0;

	while (h)
	{
		_puts(h->str ? h->str : "(nill)");
		_puts("\n");
		h = h->next;
		j++;
	}
	return (j);
}

/**
 * delete_node - Deletes node at given index.
 * @head: Address of pointer to first node.
 * @index: Index of node to delete.
 *
 * Return: 1 on success, 0 on failure
 */

int delete_node(list_t **head, unsigned int index)
{
	list_t *node, *prev_node;
	unsigned int j = 0;

	if (!head || !*head)
		return (0);
	if (!index)
	{
		node = *head;
		*head = (*head)->next;
		free(node->str);
		free(node);
		return (1);
	}
	node = *head;
	while (node)
	{
		if (j == index)
		{
			prev_node->next = node->next;
			free(node->str);
			free(node);
			return (1);
		}
		j++;
		prev_node = node;
		node = node->next;
	}
	return (0);
}

/**
 * free_list - Frees all nodes of a list.
 * @head_ptr: Address of pointer to head node
 *
 * Return: Void
 */

void free_list(list_t **head_ptr)
{
	list_t *node, *next_node, *head;

	if (!head_ptr || !*head_ptr)
		return;
	head = *head_ptr;
	node = head;
	while (node)
	{
		next_node = node->next;
		free(node->str);
		free(node);
		node = next_node;
	}
	*head_ptr = NULL;
}
