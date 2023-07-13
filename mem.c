#include "shell.h"

/**
 * be_free - Frees a pointer and NULLs address.
 * @ptr: Address of the pointer to free
 * Return: 1 if freed, otherwise 0.
 */

int be_free(void **ptr)
{
	if (ptr && *ptr)
	{
		free(*ptr);
		*ptr = NULL;
		return (1);
	}
	return (0);
}
