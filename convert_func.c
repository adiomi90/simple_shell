#include "main.h"

/**
 * err_atoi - converts a string to decimal
 * @str: error string
 * Return: converted number, -1 on error
 */
int err_atoi(char *str)
{
	int i = 0;
	unsigned long int num = 0;

	if (*str == '+')
		str++;
	for (i = 0;  str[i]; i++)
	{
		if (str[i] >= '0' && str[i] <= '9')
		{
			num = num * 10 + (str[i] - '0');
			if (num > INT_MAX)
				return (-1);
		}
		else
			return (-1);
	}
	return (num);
}

/**
 * dec_print - prints an integer
 * @num: input integer number
 * @fd: filedescriptor
 * Return: count of printed chars
 */
int dec_print(int num, int fd)
{
	int (*_putc)(char) = _putchar;
	int j, ret = 0;
	unsigned int abs_num, cur;

	if (fd == STDERR_FILENO)
		_putc = err_putc;
	if (num < 0)
	{
		abs_num = -num;
		_putc('-');
		ret++;
	}
	else
		abs_num = num;
	cur = abs_num;
	for (j = 1000000000; j > 1; j /= 10)
	{
		if (abs_num / j)
		{
			_putc('0' + cur / j);
			ret++;
		}
		cur %= j;
	}
	_putc('0' + cur);
	ret++;

	return (ret);
}

/**
 * _convert_num- converts a hexadecimal number
 * @num: input number
 * @base: input base
 * @flag: argument flags
 * Return: string
 */
char *_convert_num(long int num, int base, int flag)
{
	static char *str;
	static char buff[50];
	char sign;
	char *ptr;
	unsigned long n = num;

	if (!(flag & CONVERT_UNSIGNED) && num < 0)
	{
		n = -num;
		sign = '-';

	}
	str = flag & CONVERT_HEX ? "0123456789abcdef" : "0123456789ABCDEF";
	ptr = &buff[49];
	*ptr = '\0';

	do	{
		*--ptr = str[n % base];
		n /= base;
	} while (n != 0);

	if (sign)
		*--ptr = sign;
	return (ptr);
}

/**
 *_atoi - converts a string to a decimal number
 *@str: string to be converted
 *Return: converted number
 */

int _atoi(char *str)
{
	int j, sign = 1, flag = 0;
	unsigned int num = 0;

	for (j = 0;  str[j] && flag != 2; j++)
	{
		if (str[j] == '-')
			sign *= -1;

		if (str[j] >= '0' && str[j] <= '9')
		{
			flag = 1;
			num = num * 10 + (str[j] - '0');
		}
		else if (flag == 1)
			flag = 2;
	}

	return (num * sign);
}

/**
 * **strtow - splits a string into words. Ingores repeated delims.
 * @str: parsed string
 * @d: delim string
 * Return: a pointer to an array of strings, NULL on failure
 */

char **strtow(char *str, char *d)
{
	int i, j, k, m, words = 0;
	char **ptr;

	if (str == NULL || str[0] == 0)
		return (NULL);
	if (!d)
		d = " ";
	for (i = 0; str[i] != '\0'; i++)
		if (!_isdelim(str[i], d) && (_isdelim(str[i + 1], d) || !str[i + 1]))
			words++;

	if (words == 0)
		return (NULL);
	ptr = malloc((1 + words) * sizeof(char *));
	if (!ptr)
		return (NULL);
	for (i = 0, j = 0; j < words; j++)
	{
		while (_isdelim(str[i], d))
			i++;
		k = 0;
		while (!_isdelim(str[i + k], d) && str[i + k])
			k++;
		ptr[j] = malloc((k + 1) * sizeof(char));
		if (!ptr[j])
		{
			for (k = 0; k < j; k++)
				free(ptr[k]);
			free(ptr);
			return (NULL);
		}
		for (m = 0; m < k; m++)
			ptr[j][m] = str[i++];
		ptr[j][m] = 0;
	}
	ptr[j] = NULL;
	return (ptr);
}
