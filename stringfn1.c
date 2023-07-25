#include "shell.h"

/**
 * _strcpy - Copies a string in the func.
 * @dest: The destination of the string copy.
 * @src: The source of the string.
 * Return: The pointer to the destination.
 */

char *_strcpy(char *dest, char *src)
{
	int j = 0;

	if (dest == src || src == 0)
		return (dest);
	while (src[j])
	{
		dest[j] = src[j];
		j++;
	}
	dest[j] = 0;
	return (dest);
}

/**
 * _strdup - Duplicates a string of a func.
 * @s: The stringto duplicate in the func.
 * Return: The pointer to the duplicated string.
 */

char *_strdup(const char *s)
{
	int len = 0;
	char *ret;

	if (s == NULL)
		return (NULL);
	while (*s++)
		len++;
	ret = malloc(sizeof(char) * (len + 1));
	if (!ret)
		return (NULL);
	for (len++; len--;)
		ret[len] = *--s;
	return (ret);
}

/**
 * _puts - Prints an input string.
 * @s: The string to be printed.
 * Return: Nothing.
 */

void _puts(char *s)
{
	int j = 0;

	if (!s)
		return;
	while (s[j] != '\0')
	{
		_putchar(s[j]);
		j++;
	}
}

/**
 * _putchar - Writes the character to print.
 * @c: The character to print.
 * Return: On success 1.
 * On error -1 reurned, and errno is set appropriately.
 */

int _putchar(char c)
{
	static int j;
	static char buffer[WRITE_BUF_SIZE];

	if (c == BUF_FLUSH || j >= WRITE_BUF_SIZE)
	{
		write(1, buffer, j);
		j = 0;
	}
	if (c != BUF_FLUSH)
		buffer[j++] = c;
	return (1);
}
