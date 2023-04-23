#include "main.h"

/**
 * err_print - controls printing of error messages
 * @info: struct containing potential arguments
 * @str: string containing error type
 */
void err_print(info_t *info, char *str)
{
	err_puts(info->fname);
	err_puts(": ");
	dec_print(info->line_count, STDERR_FILENO);
	err_puts(": ");
	err_puts(info->argv[0]);
	err_puts(": ");
	err_puts(str);
}

/**
 * err_puts - for printing error string
 * @str: string to be printed
 * Return: Nothing
 */
void err_puts(char *str)
{
	while (*str)
	{
		err_putc(*str);
		str++;
	}
}

/**
 * err_putc - for writing error chars
 * @c: char to be print
 * Return: On success 1, on error, -1.
 */
int err_putc(char c)
{
	static int len;
	static char buff[BUFF_SIZE];

	if (c == BUFF_FLUSH || len >= BUFF_SIZE)
	{
		write(2, buff, len);
		len = 0;
	}
	if (c != BUFF_FLUSH)
		buff[len++] = c;
	return (1);
}

/**
 * fd_putc - for writing chars to a specified fd
 * @c: char to print
 * @fd: file descriptor
 * Return: On success 1, on error, -1.
 */
int fd_putc(char c, int fd)
{
	static int len;
	static char buff[BUFF_SIZE];

	if (c == BUFF_FLUSH || len >= BUFF_SIZE)
	{
		write(fd, buff, len);
		len = 0;
	}
	if (c != BUFF_FLUSH)
		buff[len++] = c;
	return (1);
}

/**
 * fd_puts - for printing a string to a given fd
 * @str: string to be printed
 * @fd: file descriptor
 * Return: number of printed chars
 */
int fd_puts(char *str, int fd)
{
	int len = 0;

	if (!str)
		return (0);
	while (*str)
	{
		len += fd_putc(*str, fd);
		str++;
	}
	return (len);
}
