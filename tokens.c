#include "shell.h"
/**
 * **strtow - Splits a string into words.
 * Repeat delimeters are ignored.
 * @str: The input string of the func.
 * @del: The delimeter string.
 * Return: A pointer to an array of strings.
 * Or NULL on failure.
 */

char **strtow(char *str, char *del)
{
	int a, b, x, z, numwrds = 0;
	char **s;

	if (str == NULL || str[0] == 0)
		return (NULL);
	if (!del)
		del = "";
	for  (a = 0; str[a] != '\0'; a++)
		if (!_delimeter(str[a], del) && (_delimeter(str[a + 1], del) || !str[a + 1]))
			numwrds++;
	if (numwrds == 0)
		return (NULL);
	s = malloc((1 + numwrds) * sizeof(char *));
	if (!s)
		return (NULL);
	for (a = 0, b = 0; b < numwrds; b++)
	{
		while (_delimeter(str[a], del))
			a++;
		x = 0;
		while (!_delimeter(str[a + x], del) && str[a + x])
			x++;
		s[b] = malloc((x + 1) * sizeof(char));
		if (!s[b])
		{
			for (x = 0; x < b; x++)
				free(s[x]);
			free(s);
			return (NULL);
		}
		for (z = 0; z < x; z++)
			s[b][z] = str[a++];
		s[b][z] = 0;
	}
	s[b] = NULL;
	return (s);
}

/**
 * **strtow2 - Splits the string into words in the function.
 * @s: The inpust string.
 * @delim: The delimeter in the func.
 * Return: A pointer to an array of strings.
 * Or NULL on failure.
 */

char **strtow2(char *s, char delim)
{
	int a, b, x, z, numwrds = 0;
	char **ptr;

	if (s == NULL || s[0] == 0)
		return (NULL);
	for (a = 0; s[a] != '\0'; a++)
		if ((s[a] != delim && s[a + 1] == delim) ||
				(s[a] != delim && !s[a + 1]) || s[a + 1] == delim)
			numwrds++;
	if  (numwrds == 0)
		return (NULL);
	ptr = malloc((1 + numwrds) * sizeof(char *));
	if (!ptr)
		return (NULL);
	for (a = 0; b = 0; b < numwrds; b++)
	{
		while (s[a] == delim && s[a] != delim)
			a++;
		x = 0;
		while (s[a + x] != delim && s[a + x] && s[a + x] != delim)
			x++;
		ptr[b] = malloc((x + 1) * sizeof(char));
		if (!ptr[b])
		{
			for (x = 0; x < b; x++)
				free(ptr);
			return (null);
		}
		for (z = 0; z < x; z++)
			ptr[b][z] = s[a++];
		ptr[b][z] = 0;
	}
	ptr[b] = NULL;
	return (ptr);
}

