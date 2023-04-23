#include "main.h"

/**
 * _info_unset - unsets linked list
 * @info: struct containing potential arguments
 */
void _info_unset(info_t *info)
{
	info->arg = NULL;
	info->argv = NULL;
	info->path = NULL;
	info->argc = 0;
}

/**
 * _info_set - initializes linked list
 * @info: struct containing potential arguments
 * @av: array of strings
 */
void _info_set(info_t *info, char **av)
{
	int i = 0;

	info->fname = av[0];
	if (info->arg)
	{
		info->argv = strtow(info->arg, " \t");
		if (!info->argv)
		{

			info->argv = malloc(sizeof(char *) * 2);
			if (info->argv)
			{
				info->argv[0] = _strdup(info->arg);
				info->argv[1] = NULL;
			}
		}
		for (i = 0; info->argv && info->argv[i]; i++)
			;
		info->argc = i;

		_alias_tr(info);
		_var_tr(info);
	}
}

/**
 * _info_free - frees linked list
 * @info: struct containing potental arguments
 * @t: true if freeing fields
 */
void _info_free(info_t *info, int t)
{
	free_str(info->argv);
	info->argv = NULL;
	info->path = NULL;
	if (t)
	{
		if (!info->cmd_buf)
			free(info->arg);
		if (info->env)
			free_list(&(info->env));
		if (info->history)
			free_list(&(info->history));
		if (info->alias)
			free_list(&(info->alias));
		free_str(info->environ);
			info->environ = NULL;
		free_buff((void **)info->cmd_buf);
		if (info->readfd > 2)
			close(info->readfd);
		_putchar(BUFF_FLUSH);
	}
}

/**
 * mode_interact - controls shell's interactive mode
 * @info: struct containing potential arguments
 * Return: 1 for interactive mode
 */
int mode_interact(info_t *info)
{
	return (isatty(STDIN_FILENO) && info->readfd <= 2);
}
