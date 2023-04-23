#include "main.h"

/**
 * _hshhistory - displays history list.
 * @info: Struct containing potential arguments.
 * Return: Always 0
 */
int _hshhistory(info_t *info)
{
	print_list(info->history);
	return (0);
}

/**
 * _hshalias - mimics alias builtin
 * @info: Struct containing potential arguments.
 * Return: Always 0
 */
int _hshalias(info_t *info)
{
	int j;
	char *ptr = NULL;
	list_t *current = NULL;

	if (info->argc == 1)
	{
		current = info->alias;
		while (current)
		{
			_alias_print(current);
			current = current->next;
		}
		return (0);
	}
	for (j = 1; info->argv[j]; j++)
	{
		ptr = _strchr(info->argv[j], '=');
		if (ptr)
			_alias_set(info, info->argv[j]);
		else
			_alias_print(node_strstart(info->alias, info->argv[j], '='));
	}

	return (0);
}


/**
 * _hshexit - shell exit builtin
 * @info: Struct containing potential arguments.
 *  Return: exits with the specified exit status
 */
int _hshexit(info_t *info)
{
	int check_exit;

	if (info->argv[1])
	{
		check_exit = err_atoi(info->argv[1]);
		if (check_exit == -1)
		{
			info->status = 2;
			err_print(info, "Illegal number: ");
			err_puts(info->argv[1]);
			err_putc('\n');
			return (1);
		}
		info->err_num = err_atoi(info->argv[1]);
		return (-2);
	}
	info->err_num = -1;
	return (-2);
}

/**
 * _hshcd - controls changes of directories
 * @info: Struct containing potential arguments.
 * Return: Always 0
 */
int _hshcd(info_t *info)
{
	char *str, *dir, buff[1024];
	int ret;

	str = getcwd(buff, 1024);
	if (!str)
		_puts("TODO: >>getcwd failure emsg here<<\n");
	if (!info->argv[1])
	{
		dir = get_env(info, "HOME=");
		if (!dir)
			ret = chdir((dir = get_env(info, "PWD=")) ? dir : "/");
		else
			ret = chdir(dir);
	}
	else if (_strcmp(info->argv[1], "-") == 0)
	{
		if (!get_env(info, "OLDPWD="))
		{
			_puts(str);
			_putchar('\n');
			return (1);
		}
		_puts(get_env(info, "OLDPWD=")), _putchar('\n');
		ret = chdir((dir = get_env(info, "OLDPWD=")) ? dir : "/");
	}
	else
		ret = chdir(info->argv[1]);
	if (ret == -1)
	{
		err_print(info, "can't cd to ");
		err_puts(info->argv[1]), err_putc('\n');
	}
	else
	{
		_setenv(info, "OLDPWD", get_env(info, "PWD="));
		_setenv(info, "PWD", getcwd(buff, 1024));
	}
	return (0);
}

/**
 * _hshhelp - controls help calls
 * @info: Struct containing potential arguments.
 * Return: Always 0
 */
int _hshhelp(info_t *info)
{
	char **ptr;

	ptr = info->argv;
	_puts("help call works. Function not yet implemented \n");
	if (0)
		_puts(*ptr);
	return (0);
}
