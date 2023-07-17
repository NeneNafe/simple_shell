#include "shell.h"

/**
 * interactive - checks if shell is in interactive mode
 * @info: struct address
 * Return: 1 in interactive mode, 0 otherwise
 */
int interactive(info_t *info)
{
	return (isatty(STDIN_FILENO) && info->readfd <= 2);
}

/**
 * delimeter - checks if a character is a delim
 * @c: the character to be checked
 * @delim: the delimeter string
 * Return: 1 if true, 0 otherwise
 */
int delimeter(char c, char *delim)
{
	while (*delim)
		if (*delim++ == c)
			return (1);
	return (0);
}

/**
 * is_alpha - checks for alphabetic character
 * @c: the character to input
 * Return: if c is alphabetic 1, otherwise 0
 */
int is_alpha(int c)
{
	if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'))
		return (1);
	else
		return (0);
}

/**
 * is_atoi - changes a string to an integer
 * @str: the string to be converted
 * Return: Success Always.
 */

int is_atoi(char *str)
{
	int j, sign = 1, flag = 0, output;
	unsigned int result = 0;

	for (j = 0; str[j] != '\0' && flag != 2; j++)
	{
		if (str[j] == '-')
			sign *= -1;
		if (str[j] >= '0' && str[j] <= '9')
		{
			flag = 1;
			result *= 10;
			result += (str[j] - '0');
		}
		else if (flag == 1)
			flag = 2;
	}

	if (sign == -1)
		output = -result;
	else
		output = result;
	return (output);
}
