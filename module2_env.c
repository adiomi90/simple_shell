#include "main.h"

/**
 * get_env - returns the value of an environmental variable
 * @info: Struct containing potential arguments.
 * @var: name of environmental variable
 * Return: value of environmental variable
 */
char *get_env(info_t *info, const char *var)
{
	list_t *current = info->env;
	char *ptr;

	while (current)
	{
		ptr = _strstart(current->str, var);
		if (ptr && *ptr)
			return (ptr);
		current = current->next;
	}
	return (NULL);
}

/**
 * _hshsetenv - sets environmental variable on hsh
 * @info: Struct containing potential arguments.
 *  Return: Always 0
 */
int _hshsetenv(info_t *info)
{
	if (info->argc != 3)
	{
		err_puts("Incorrect number of arguements\n");
		return (1);
	}
	if (_setenv(info, info->argv[1], info->argv[2]))
		return (0);
	return (1);
}

/**
 * _hshunsetenv - unsets an environmental variable on hsh
 * @info: Struct containing potential arguments.
 *  Return: Always 0
 */
int _hshunsetenv(info_t *info)
{
	int i;

	if (info->argc == 1)
	{
		err_puts("Too few arguements.\n");
		return (1);
	}
	for (i = 1; i <= info->argc; i++)
		_unsetenv(info, info->argv[i]);

	return (0);
}

/**
 * fill_env_list - populates the new environment
 * @info: Struct containing potential arguments.
 * Return: Always 0
 */
int fill_env_list(info_t *info)
{
	list_t *current = NULL;
	size_t i;

	for (i = 0; environ[i]; i++)
		add_node_end(&current, environ[i], 0);
	info->env = current;
	return (0);
}
