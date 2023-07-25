#include "shell.h"

/**
 * _strncpy - copies a string
 * @des: the destination where the str is copied
 * @source: the main source if the str
 * @n: the n characters to be copied
 * Return: Success.
 */
char *_strncpy(char *des, char *source, int n)
{
	int j, k;
	char *str = des;

	j = 0;
	while (source[j] != '\0' && j < n - 1)
	{
		des[j] = source[j];
		j++;
	}
	if (j < n)
	{
		k = j;
		while (k < n)
		{
			des[k] = '\0';
			k++;
		}
	}
	return (str);
}

/**
 * _strncat - concatenates two strings
 * @des: the destnation
 * @source: where it starts from
 * @n: n characters to be used
 * Return: Always Success.
 */
char *_strncat(char *des, char *source, int n)
{
	int j, k;
	char *str = des;

	j = 0;
	k = 0;
	while (des[j] != '\0')
		j++;
	while (source[k] != '\0' && k < n)
	{
		des[j] = source[k];
		j++;
		k++;
	}
	if (k < n)
		des[j] = '\0';
	return (str);
}

/**
 * our_strchr - locates a char in a string
 * @str: the string to be parsed
 * @c: the character used
 * Return: Always Succes.
 */
char *our_strchr(char *str, char c)
{
	do {
		if (*str == c)
			return (str);
	} while (*str++ != '\0');

	return (NULL);
}
