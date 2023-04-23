#include "main.h"

/**
 * _isdelim - checks for delim chars
 * @c: char to check
 * @d: delimeter string
 * Return: 1 if true, otherwise 0
 */
int _isdelim(char c, char *d)
{
	while (*d)
	{
		if (*d == c)
			return (1);
		d++;
	}
	return (0);
}

/**
 *_isalpha - checks for alphabets
 *@c: char to check
 *Return: 1 if true, 0 otherwise
 */

int _isalpha(int c)
{
	if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'))
		return (1);
	else
		return (0);
}

/**
 * handle_comments - checks and removes comments
 * @buff: string to modify
 * Return: Always 0
 */
void handle_comments(char *buff)
{
	int j;

	for (j = 0; buff[j]; j++)
		if (buff[j] == '#' && (!j || buff[j - 1] == ' '))
		{
			buff[j] = '\0';
			break;
		}
}

/**
 *_puts - for printing a string to STDOUT
 *@str: string to be printed
 * Return: Nothing
 */
void _puts(char *str)
{
	int i = 0;

	if (!str)
		return;
	while (str[i] != '\0')
	{
		_putchar(str[i]);
		i++;
	}
}

/**
 * _putchar - for writing chars to STDOUT
 * @c: chars to print
 * Return: On success 1, on error, -1.
 */
int _putchar(char c)
{
	static int i;
	static char buf[BUFF_SIZE];

	if (c == BUFF_FLUSH || i >= BUFF_SIZE)
	{
		write(1, buf, i);
		i = 0;
	}
	if (c != BUFF_FLUSH)
		buf[i++] = c;
	return (1);
}
