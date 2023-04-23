#include "main.h"

/**
 * _alias_unset - unsets the alias
 * @info: struct containing potential arguments
 * @str: string alias
 * Return: 0 on success, 1 otherwise
 */
int _alias_unset(info_t *info, char *str)
{
	int ret;
	char *ptr, c;

	ptr = _strchr(str, '=');
	if (!ptr)
		return (1);
	c = *ptr;
	*ptr = 0;
	ret = delete_node_index(&(info->alias),
		get_node_index(info->alias, node_strstart(info->alias, str, -1)));
	*ptr = c;
	return (ret);
}

/**
 * _alias_set - sets alias to string
 * @info: struct containing potential arguments
 * @str: string alias
 * Return: 0 on success, 1 otherwise
 */
int _alias_set(info_t *info, char *str)
{
	char *ptr;

	ptr = _strchr(str, '=');
	if (!ptr)
		return (1);
	if (!*++ptr)
		return (_alias_unset(info, str));

	_alias_unset(info, str);
	return (add_node_end(&(info->alias), str, 0) == NULL);
}

/**
 * _alias_print - prints an alias string
 * @current: the alias node
 * Return: Always 0 on success, 1 on error
 */
int _alias_print(list_t *current)
{
	char *ptr = NULL, *s = NULL;

	if (current)
	{
		ptr = _strchr(current->str, '=');
		for (s = current->str; s <= ptr; s++)
			_putchar(*s);
		_putchar('\'');
		_puts(ptr + 1);
		_puts("'\n");
		return (0);
	}
	return (1);
}
