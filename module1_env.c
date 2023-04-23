#include "main.h"

/**
 * _hshenv - prints contents of the current environment
 * @info: Struct containing potential arguments.
 * Return: Always 0
 */
int _hshenv(info_t *info)
{
	print_liststr(info->env);
	return (0);
}


/**
 * _get_hshenv - returns a string array copy of hsh environment.
 * @info: Struct containing potential arguments.
 * Return: Always 0
 */
char **_get_hshenv(info_t *info)
{
	if (!info->environ || info->env_changed)
	{
		info->environ = str_from_list(info->env);
		info->env_changed = 0;
	}

	return (info->environ);
}

/**
 * _unsetenv - unsets an environment variable
 * @info: Struct containing potential arguments.
 *  Return: 1 on success, 0 otherwise
 * @var: string property of environmental variable
 */
int _unsetenv(info_t *info, char *var)
{
	list_t *current = info->env;
	size_t index = 0;
	char *ptr;

	if (!current || !var)
		return (0);

	while (current)
	{
		ptr = _strstart(current->str, var);
		if (ptr && *ptr == '=')
		{
			info->env_changed = delete_node_index(&(info->env), index);
			index = 0;
			current = info->env;
			continue;
		}
		current = current->next;
		index++;
	}
	return (info->env_changed);
}

/**
 * _setenv - sets an environmental variable
 * @info: Struct containing potential arguments.
 * @var: string property of environmental variable
 * @val: string value of environmental  variable
 *  Return: Always 0
 */
int _setenv(info_t *info, char *var, char *val)
{
	char *buff = NULL;
	list_t *current;
	char *ptr;

	if (!var || !val)
		return (0);

	buff = malloc(_strlen(var) + _strlen(val) + 2);
	if (!buff)
		return (1);
	_strcpy(buff, var);
	_strcat(buff, "=");
	_strcat(buff, val);
	current = info->env;
	while (current)
	{
		ptr = _strstart(current->str, var);
		if (ptr && *ptr == '=')
		{
			free(current->str);
			current->str = buff;
			info->env_changed = 1;
			return (0);
		}
		current = current->next;
	}
	add_node_end(&(info->env), buff, 0);
	free(buff);
	info->env_changed = 1;
	return (0);
}
