#include "main.h"

/**
 * loop_hsh - Custom shell loop
 * @info: struct containing potential arguments
 * @av: string array of command line arguments
 * Return: 0 on success, appropriate exit code on error
 */
int loop_hsh(info_t *info, char **av)
{
	ssize_t len = 0;
	int ret = 0;

	while (len != -1 && ret != -2)
	{
		_info_unset(info);
		if (mode_interact(info))
			_puts("$ ");
		err_putc(BUFF_FLUSH);
		len = _getinput(info);
		if (len != -1)
		{
			_info_set(info, av);
			ret = search_builtin(info);
			if (ret == -1)
				_trace_cmd(info);
		}
		else if (mode_interact(info))
			_putchar('\n');
		_info_free(info, 0);
	}
	hist_write(info);
	_info_free(info, 1);
	if (!mode_interact(info) && info->status)
		exit(info->status);
	if (ret == -2)
	{
		if (info->err_num == -1)
			exit(info->status);
		exit(info->err_num);
	}
	return (ret);
}

/**
 * search_builtin - looks for a builtin command
 * @info: struct containing potential arguments
 * Return: the appropriate exit code
 */
int search_builtin(info_t *info)
{
	int i, ret = -1;
	builtin_t builtintable[] = {
		{"exit", _hshexit},
		{"env", _hshenv},
		{"help", _hshhelp},
		{"history", _hshhistory},
		{"setenv", _hshsetenv},
		{"unsetenv", _hshunsetenv},
		{"cd", _hshcd},
		{"alias", _hshalias},
		{NULL, NULL}
	};

	for (i = 0; builtintable[i].type; i++)
		if (_strcmp(info->argv[0], builtintable[i].type) == 0)
		{
			info->line_count++;
			ret = builtintable[i].func(info);
			break;
		}
	return (ret);
}

/**
 * _trace_cmd - trace the command in PATH
 * @info: struct containing potential arguments
 * Return: Nothing
 */
void _trace_cmd(info_t *info)
{
	char *path = NULL;
	int i, count;

	info->path = info->argv[0];
	if (info->linecount_flag == 1)
	{
		info->line_count++;
		info->linecount_flag = 0;
	}
	for (i = 0, count = 0; info->arg[i]; i++)
		if (!_isdelim(info->arg[i], " \t\n"))
			count++;
	if (!count)
		return;

	path = _path_trace(info, get_env(info, "PATH="), info->argv[0]);
	if (path)
	{
		info->path = path;
		_forkcmd(info);
	}
	else
	{
		if ((mode_interact(info) || get_env(info, "PATH=")
			|| info->argv[0][0] == '/') && _iscmd(info, info->argv[0]))
			_forkcmd(info);
		else if (*(info->arg) != '\n')
		{
			info->status = 127;
			err_print(info, "not found\n");
		}
	}
}

/**
 * _forkcmd - forks a an executed thread to run cmd
 * @info: struct containing potential arguments
 * Return: Nothing
 */
void _forkcmd(info_t *info)
{
	pid_t _chpid;

	_chpid = fork();
	if (_chpid == -1)
	{
		perror("Error:");
		return;
	}
	if (_chpid == 0)
	{
		if (execve(info->path, info->argv, _get_hshenv(info)) == -1)
		{
			_info_free(info, 1);
			if (errno == EACCES)
				exit(126);
			exit(1);
		}
	}
	else
	{
		wait(&(info->status));
		if (WIFEXITED(info->status))
		{
			info->status = WEXITSTATUS(info->status);
			if (info->status == 126)
				err_print(info, "Permission denied\n");
		}
	}
}
