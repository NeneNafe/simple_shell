#include "shell.h"

/**
 * get_hist_file - Gets the history file.
 * @info: Parameter struct.
 *
 * Return: Allocated string containing hisstory file.
 */

char *get_hist_file(info_t *info)
{
	char *buf, *dir;

	dir = our_getenv(info, "HOME=");
	if (!dir)
		return (NULL);
	buf = malloc(sizeof(char) * (_strlen(dir) + _strlen(HIST_FILE) + 2));
	if (!buf)
		return (NULL);
	buf[0] = 0;
	_strcpy(buf, dir);
	_strcat(buf, "/");
	_strcat(buf, HIST_FILE);
	return (buf);
}

/**
 * write_hist - Creates a file, or appends to an existing file.
 * @info: The parameter struct.
 *
 * Return: 1 on success, else -1.
 */

int write_hist(info_t *info)
{
	ssize_t fd;
	char *filename = get_hist_file(info);
	list_t *node = NULL;

	if (!filename)
		return (-1);
	fd = open(filename, O_CREAT | O_TRUNC | O_RDWR, 0644);
	free(filename);
	if (fd == -1)
		return (-1);
	for (node = info->his; node; node = node->next)
	{
		_printfd(node->str, fd);
		put_fd('\n', fd);
	}
	put_fd(BUF_FLUSH, fd);
	close(fd);
	return (1);
}

/**
 * read_hist - Reads history from file.
 * @info: The parameter struct.
 *
 * Return: Histcounton success, 0 otherwise.
 */

int read_hist(info_t *info)
{
	int i, last = 0, linecount = 0;
	ssize_t fd, rdlen, fsize = 0;
	struct stat st;
	char *buf = NULL, *filename = get_hist_file(info);

	if (!filename)
		return (0);
	fd = open(filename, O_RDONLY);
	free(filename);
	if (fd == -1)
		return (0);
	if (!fstat(fd, &st))
		fsize = st.st_size;
	if (fsize < 2)
		return (0);
	buf = malloc(sizeof(char) * (fsize + 1));
	if (!buf)
		return (0);
	rdlen = read(fd, buf, fsize);
	buf[fsize] = 0;
	if (rdlen <= 0)
		return (free(buf), 0);
	close(fd);
	for (i = 0; i < fsize; i++)
		if (buf[i] == '\n')
		{
			buf[i] = 0;
			build_hist_list(info, buf + last, linecount++);
			last = i + 1;
		}
	if (last != i)
		build_hist_list(info, buf + last, linecount++);
	free(buf);
	info->histcount = linecount;
	while (info->histcount-- >= HIST_MAX)
		delete_node(&(info->his), 0);
	renumber_hist(info);
	return (info->histcount);
}

/**
 * build_hist_list - Adds entry to a history linked list.
 * @info: Structure containing potential arguments used to maintain.
 * @buf: Buffer.
 * @linecount: The history linecount, histcount
 *
 * Return: Always 0.
 */
int build_hist_list(info_t *info, char *buf, int linecount)
{
	list_t *node = NULL;

	if (info->his)
		node = info->his;
	add_node_end(&node, buf, linecount);
	if (!info->his)
		info->his = node;
	return (0);
}

/**
 * renumber_hist - Renumbers the history linked list after changes.
 * @info: Structure containing potential arguments used to maintain.
 *
 * Return: The new histcount.
 */

int renumber_hist(info_t *info)
{
	list_t *node = info->his;
	int j = 0;

	while (node)
	{
		node->num = j++;
		node = node->next;
	}
	return (info->histcount = j);
}
