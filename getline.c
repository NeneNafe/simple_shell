#include "shell.h"

/**
 * input_buffer - Bufferschained commands.
 * @info: Param struct.
 * @buf: Address of buffer.
 * @len: Address of len var.
 * Return: Bytes read.
 */

ssize_t input_buffer(info_t *info, char **buf, size_t *len)
{
	ssize_t r = 0;
	size_t len_p = 0;

	if (!*len)
	{
		free(*buf);
		*buf = NULL;
		signal(SIGINT, sigintHandler);
#if USE_GETLINE
		r = getline(buf, &len_p, stdin);
#else
		r = get_getline(info, buf, &len_p);
#endif
		if (r > 0)
		{
			if ((*buf)[r - 1] == '\n')
			{
				(*buf)[r - 1] = '\0';
				r--;
			}
			info->linecount_flag = 1;
			rm_comments(*buf);
			build_hist_list(info, *buf, info->histcount++);
			{
				*len = r;
				info->cmd_buf = buf;
			}
		}
	}
	return (r);
}

/**
 * get_input - Gets a line minus the newline.
 * @info: Param struct
 *
 * Return: Bytes read.
 */

ssize_t get_input(info_t *info)
{
	static char *buf;
	static size_t i, j, len;
	ssize_t r = 0;
	char **buf_p = &(info->arg), *ptr;

	_putchar(BUF_FLUSH);
	r = input_buffer(info, &buf, &len);
	if (r == -1) /* EOF */
		return (-1);
	if (len)
	{
		j = i;
		ptr = buf + i;

		check_chain(info, buf, &j, i, len);
		while (j < len)
		{
			if (is_chain(info, buf, &j))
				break;
			j++;
		}
		i = j + 1;
		if (i >= len)
		{
			i = len = 0;
			info->cmd_buf_type = CMD_NORM;
		}
		*buf_p = ptr;
		return (_strlen(ptr));
	}
	*buf_p = buf;
	return (r);
}

/**
 * read_buffer - Reads a buffer.
 * @info: Param struct.
 * @buf: Buffer.
 * @i: size
 *
 * Return: r
 */

ssize_t read_buffer(info_t *info, char *buf, size_t *i)
{
	ssize_t r = 0;

	if (*i)
		return (0);
	r = read(info->readfd, buf, READ_BUF_SIZE);
	if (r >= 0)
		*i = r;
	return (r);
}

/**
 * get_getline - Gets the next line of input from STDIN.
 * @info: Param struct.
 * @ptr: Address of pointer to buffer, preallocated or NULL.
 * @length: Size of reallocated ptr buffer if not NULL.
 *
 * Return: Success.
 */

int get_getline(info_t *info, char **ptr, size_t *length)
{
	static char buf[READ_BUF_SIZE];
	static size_t i, len;
	size_t k;
	ssize_t r = 0, str = 0;
	char *p = NULL, *new_p = NULL, *c;

	p = *ptr;
	if (p && length)
		str = *length;
	if (i == len)
		i = len = 0;
	r = read_buffer(info, buf, &len);
	if (r == -1 || (r == 0 && len == 0))
		return (-1);

	c = our_strchr(buf + i, '\n');
	k = c ? 1 + (unsigned int)(c - buf) : len;
	new_p = our_realloc(p, str, str ? str + k : k + 1);
	if (!new_p) /* MALLOC FAILURE */
		return (p ? free(p), -1 : -1);

	if (str)
		_strncat(new_p, buf + i, k - i);
	else
		_strncpy(new_p, buf + i, k - i + 1);
	str += k - i;
	i = k;
	p = new_p;

	if (length)
		*length = str;
	*ptr = p;
	return (str);
}

/**
 * sigintHandler - Blocks ctrl-C
 * @sig_num: The signal number.
 *
 * Return: void.
 */

void sigintHandler(__attribute__((unused))int sig_num)
{
	_puts("\n");
	_puts("$ ");
	_putchar(BUF_FLUSH);
}
