#include "main.h"

/**
 * _iscmd - checks if file is executable command
 * @info: struct containibg potential arguments
 * @path: file file
 * Return: 1 if true, 0 otherwise
 */
int _iscmd(info_t *info, char *path)
{
	struct stat st;

	(void)info;
	if (!path || stat(path, &st))
		return (0);

	if (st.st_mode & S_IFREG)
	{
		return (1);
	}
	return (0);
}

/**
 * _chars_dup - duplicates chars
 * @path: PATH list
 * @start: start index
 * @stop: stop index
 * Return: pointer to duplicated chars
 */
char *_chars_dup(char *path, int start, int stop)
{
	static char buff[1024];
	int i = 0, k = 0;

	for (k = 0, i = start; i < stop; i++)
		if (path[i] != ':')
			buff[k++] = path[i];
	buff[k] = 0;
	return (buff);
}

/**
 * _path_trace - searches for cmd in the PATH list
 * @info: struct containing potential arguments
 * @path: PATH list
 * @cmd: command to find
 * Return: path of command if found, NULL otherwise
 */
char *_path_trace(info_t *info, char *path, char *cmd)
{
	int i = 0, pos = 0;
	char *p;

	if (!path)
		return (NULL);
	if ((_strlen(cmd) > 2) && _strstart(cmd, "./"))
	{
		if (_iscmd(info, cmd))
			return (cmd);
	}
	while (1)
	{
		if (!path[i] || path[i] == ':')
		{
			p = _chars_dup(path, pos, i);
			if (!*p)
				_strcat(p, cmd);
			else
			{
				_strcat(p, "/");
				_strcat(p, cmd);
			}
			if (_iscmd(info, p))
				return (p);
			if (!path[i])
				break;
			pos = i;
		}
		i++;
	}
	return (NULL);
}
