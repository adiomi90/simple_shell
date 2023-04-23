#include "main.h"

/**
 * hist_get - for retrieving the history file
 * @info: struct containing potential arguments
 * Return: malloc'd string of history file
 */
char *hist_get(info_t *info)
{
	char *buff, *dir;

	dir = get_env(info, "HOME=");
	if (!dir)
		return (NULL);
	buff = malloc(sizeof(char) * (_strlen(dir) + _strlen(HIST_FILE) + 2));
	if (!buff)
		return (NULL);
	buff[0] = 0;
	_strcpy(buff, dir);
	_strcat(buff, "/");
	_strcat(buff, HIST_FILE);
	return (buff);
}

/**
 * hist_write - for writing or appending contents to a history file
 * @info: struct containing potential arguments
 * Return: 1 on success, -1 otherwise
 */
int hist_write(info_t *info)
{
	ssize_t fd;
	char *fname = hist_get(info);
	list_t *current = NULL;

	if (!fname)
		return (-1);

	fd = open(fname, O_CREAT | O_TRUNC | O_RDWR, 0644);
	free(fname);
	if (fd == -1)
		return (-1);
	for (current = info->history; current; current = current->next)
	{
		fd_puts(current->str, fd);
		fd_putc('\n', fd);
	}
	fd_putc(BUFF_FLUSH, fd);
	close(fd);
	return (1);
}

/**
 * hist_read - for reading history file
 * @info: struct containing potential arguments
 * Return: history line number count
 */
int hist_read(info_t *info)
{
	int i, last = 0, linecount = 0;
	ssize_t fd, len, fsize = 0;
	struct stat st;
	char *buff = NULL, *fname = hist_get(info);

	if (!fname)
		return (0);

	fd = open(fname, O_RDONLY);
	free(fname);
	if (fd == -1)
		return (0);
	if (!fstat(fd, &st))
		fsize = st.st_size;
	if (fsize < 2)
		return (0);
	buff = malloc(sizeof(char) * (fsize + 1));
	if (!buff)
		return (0);
	len = read(fd, buff, fsize);
	buff[fsize] = 0;
	if (len <= 0)
		return (free(buff), 0);
	close(fd);
	for (i = 0; i < fsize; i++)
		if (buff[i] == '\n')
		{
			buff[i] = 0;
			hist_build(info, buff + last, linecount++);
			last = i + 1;
		}
	if (last != i)
		hist_build(info, buff + last, linecount++);
	free(buff);
	info->histcount = linecount;
	while (info->histcount-- >= HIST_MAX)
		delete_node_index(&(info->history), 0);
	hist_renum(info);
	return (info->histcount);
}

/**
 * hist_build - for adding new entries to history list
 * @info: Struct containing potential arguments.
 * @buff: history buffer
 * @linecount: history line count
 * Return: Always 0
 */
int hist_build(info_t *info, char *buff, int linecount)
{
	list_t *current = NULL;

	if (info->history)
		current = info->history;
	add_node_end(&current, buff, linecount);

	if (!info->history)
		info->history = current;
	return (0);
}

/**
 * hist_renum - renumbers the history linked list after changes
 * @info: Struct containing potential arguments.
 * Return: history line count
 */
int hist_renum(info_t *info)
{
	list_t *current = info->history;
	int linecount = 0;

	while (current)
	{
		current->num = linecount++;
		current = current->next;
	}
	return (info->histcount = linecount);
}
