#include "shell.h"

/**
 * our_memset - Fills memory with a constant byte.
 * @s: The pointer to the memory area.
 * @b: The byte to fill *s with.
 * @n: The amount of bytes to be filled.
 * Return: (s) a pointer to the memory s
 */

char *our_memset(char *s, char b, unsigned int n)
{
	unsigned int j = 0;

	for (j = 0; j < n; j++)
		s[j] = b;
	return (s);
}

/**
 * free_str - Frees a string of strings.
 * @ss: The string of strings.
 */

void free_str(char **ss)
{
	char **a = ss;

	if (!ss)
		return;
	while (*ss)
		free(*ss++);
	free(a);
}

/**
 * our_realloc - Reallocates a block of memory.
 * @ptr: Pointer to previous malloc'ated block.
 * @old: Byte size of previous block.
 * @newsize: Byte size of new block.
 * Return: Pointer to da ol'block nameen.
 */

void *our_realloc(void *ptr, unsigned int old, unsigned int newsize)
{
	char *p;

	if (!ptr)
		return (malloc(newsize));
	if (!newsize)
		return (free(ptr), NULL);
	if (newsize == old)
		return (ptr);

	p = malloc(newsize);
	if (!p)
		return (NULL);

	old = old < newsize ? old : newsize;
	while (old--)
		p[old] = ((char *)ptr)[old];
	free(ptr);
	return (p);
}


