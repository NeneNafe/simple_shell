#include "shell.h"

/**
 * _nputs - prints input string
 * @s: the string to be used
 * Return: Nothing
 */
void _nputs(char *s)
{
	int j = 0;

	if (!s)
		return;
	while (s[j] != '\0')
	{
		_cputchar(s[j]);
		j++;
	}
}

/**
 * _cputchar - writes a character c to stderr
 * @c: The character to be printed
 * Return: On success 1, otherwise 0.
 */
int _cputchar(char c)
{
	static int j;
	static char buff[WRITE_BUF_SIZE];

	if (c == BUF_FLUSH || j >= WRITE_BUF_SIZE)
	{
		write(2, buff, j);
		j = 0;
	}
	if (c != BUF_FLUSH)
		buff[j++] = c;
	return (1);
}

/**
 * put_fd - writes the char to a give fd
 * @c: the character to be written
 * @fd: the file dscriptor
 * Return: On success 1, otherwise 0
 */
int put_fd(char c, int fd)
{
	static int j;
	static char buff[WRITE_BUF_SIZE];

	if (c == BUF_FLUSH || j >= WRITE_BUF_SIZE)
	{
		write(fd, buff, j);
		j = 0;
	}
	if (c != BUF_FLUSH)
		buff[j++] = c;
	return (1);
}

/**
 * _printfd - prints an input string
 * @s: the string to be printed
 * @fd: file descriptor to write to
 * Return: Number of chars used
 */
int _printfd(char *s, int fd)
{
	int j = 0;

	if (!s)
		return (0);
	while (*s)
	{
		j += put_fd(*s++, fd);
	}
	return (j);
}
