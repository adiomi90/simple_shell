#include "main.h"

/**
 * _buff_input - handles buffer command chaining
 * @info: struct containing potential arguments
 * @buff: address of buffer
 * @size: pointer to buffer size
 * Return: number of bytes read
 */
ssize_t _buff_input(info_t *info, char **buff, size_t *size)
{
	ssize_t r_count = 0;
	size_t len = 0;

	if (!*size)
	{
		free(*buff);
		*buff = NULL;
		signal(SIGINT, _sigint_handle);
#if USE_GETLINE
		r_count = getline(buff, &len, stdin);
#else
		r_count = get_line(info, buff, &len);
#endif
		if (r_count > 0)
		{
			if ((*buff)[r_count - 1] == '\n') /* remove trailing '\n' */
			{
				(*buff)[r_count - 1] = '\0';
				r_count--;
			}
			info->linecount_flag = 1;
			handle_comments(*buff);
			hist_build(info, *buff, info->histcount++);
			 /* Check for command chains */
			if (_strchr(*buff, ';') || _strstr(*buff, "&&") || _strstr(*buff, "||"))
			{
				*size = r_count;
				info->cmd_buf = buff;
			}
		}
	}
	return (r_count);
}

/**
 * _getinput - gets user input from STDIN
 * @info: struct containing potential arguments
 * Return: number of bytes read
 */
ssize_t _getinput(info_t *info)
{
	static char *buff;
	static size_t i, j, len;
	ssize_t r_count = 0;
	char **buffp = &(info->arg), *ptr;

	_putchar(BUFF_FLUSH);
	r_count = _buff_input(info, &buff, &len);
	if (r_count == -1)
		return (-1);
	if (len)
	{
		j = i;
		ptr = buff + i;

		_chain_check(info, buff, &j, i, len);
		while (j < len)
		{
			if (_ischain(info, buff, &j))
				break;
			j++;
		}

		i = j + 1;
		if (i >= len)
		{
			i = len = 0;
			info->cmd_buf_type = CMD_NORM;
		}

		*buffp = ptr;
		return (_strlen(ptr));
	}

	*buffp = buff;
	return (r_count);
}

/**
 * _buff_read - reads the buffer
 * @info: struct containing potential arguments
 * @buff: buffer
 * @size: pointer to buffer size
 * Return: number of bytes read
 */
ssize_t _buff_read(info_t *info, char *buff, size_t *size)
{
	ssize_t r_count = 0;

	if (*size)
		return (0);
	r_count = read(info->readfd, buff, BUFF_SIZE);
	if (r_count >= 0)
		*size = r_count;
	return (r_count);
}

/**
 * get_line - retrieves the next line of input from STDIN
 * @info: struct containing potential arguments
 * @ptr: double pointer to buffer
 * @size: size of malloc'd buffer if not NULL
 * Return: length of next line
 */
int get_line(info_t *info, char **ptr, size_t *size)
{
	static char buff[BUFF_SIZE];
	static size_t i, len;
	size_t k;
	ssize_t r_count = 0, s = 0;
	char *p = NULL, *new_p = NULL, *c;

	p = *ptr;
	if (p && size)
		s = *size;
	if (i == len)
		i = len = 0;

	r_count = _buff_read(info, buff, &len);
	if (r_count == -1 || (r_count == 0 && len == 0))
		return (-1);

	c = _strchr(buff + i, '\n');
	k = c ? 1 + (unsigned int)(c - buff) : len;
	new_p = _realloc(p, s, s ? s + k : k + 1);
	if (!new_p)
		return (p ? free(p), -1 : -1);

	if (s)
		_strncat(new_p, buff + i, k - i);
	else
		_strncpy(new_p, buff + i, k - i + 1);

	s += k - i;
	i = k;
	p = new_p;

	if (size)
		*size = s;
	*ptr = p;
	return (s);
}

/**
 * _sigint_handle - blocks CTRL-C
 * @sig_num: signal inumber
 * Return: Nothing
 */
void _sigint_handle(__attribute__((unused))int sig_num)
{
	_puts("\n");
	_puts("$ ");
	_putchar(BUFF_FLUSH);
}
