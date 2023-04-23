#include "main.h"

/**
 * _ischain - checks for chain delim in buffer
 * @info: struct containing potential arguments
 * @buff: char buffer
 * @ptr: address of current position in buffer
 * Return: 1 if success, 0 otherwise
 */
int _ischain(info_t *info, char *buff, size_t *ptr)
{
	size_t index = *ptr;

	if (buff[index] == '|' && buff[index + 1] == '|')
	{
		buff[index] = 0;
		index++;
		info->cmd_buf_type = CMD_OR;
	}
	else if (buff[index] == '&' && buff[index + 1] == '&')
	{
		buff[index] = 0;
		index++;
		info->cmd_buf_type = CMD_AND;
	}
	else if (buff[index] == ';')
	{
		buff[index] = 0;
		info->cmd_buf_type = CMD_CHAIN;
	}
	else
		return (0);
	*ptr = index;
	return (1);
}

/**
 * _chain_check - check for chaining continuation based on last status
 * @info: struct containing potential arguments
 * @buff: char buffer
 * @ptr: pointer to current buffer position
 * @st: starting position in buffer
 * @len: buffer length
 * Return: Nothing
 */
void _chain_check(info_t *info, char *buff, size_t *ptr, size_t st, size_t len)
{
	size_t index = *ptr;

	if (info->cmd_buf_type == CMD_AND)
	{
		if (info->status)
		{
			buff[st] = 0;
			index = len;
		}
	}
	if (info->cmd_buf_type == CMD_OR)
	{
		if (!info->status)
		{
			buff[st] = 0;
			index = len;
		}
	}

	*ptr = index;
}

/**
 * _alias_tr - replaces aliases in tokenized string
 * @info: struct containing potential arguments
 * Return: 1 if successful, 0 otherwise
 */
int _alias_tr(info_t *info)
{
	int j;
	list_t *current;
	char *ptr;

	for (j = 0; j < 10; j++)
	{
		current = node_strstart(info->alias, info->argv[0], '=');
		if (!current)
			return (0);
		free(info->argv[0]);
		ptr = _strchr(current->str, '=');
		if (!ptr)
			return (0);
		ptr = _strdup(ptr + 1);
		if (!ptr)
			return (0);
		info->argv[0] = ptr;
	}
	return (1);
}

/**
 * _var_tr - replaces variables in the tokenized string
 * @info: struct containing potential arguments
 * Return: 1 if successful, 0 otherwise
 */
int _var_tr(info_t *info)
{
	int j;
	list_t *current;

	for (j = 0; info->argv[j]; j++)
	{
		if (info->argv[j][0] != '$' || !info->argv[j][1])
			continue;

		if (!_strcmp(info->argv[j], "$?"))
		{
			_str_tr(&(info->argv[j]),
				_strdup(_convert_num(info->status, 10, 0)));
			continue;
		}
		if (!_strcmp(info->argv[j], "$$"))
		{
			_str_tr(&(info->argv[j]),
				_strdup(_convert_num(getpid(), 10, 0)));
			continue;
		}
		current = node_strstart(info->env, &info->argv[j][1], '=');
		if (current)
		{
			_str_tr(&(info->argv[j]),
				_strdup(_strchr(current->str, '=') + 1));
			continue;
		}
		_str_tr(&info->argv[j], _strdup(""));

	}
	return (0);
}

/**
 * _str_tr - replaces an old string
 * @old: pointer to old string
 * @new_str: new string
 * Return: 1 if succesful, 0 otherwise
 */
int _str_tr(char **old, char *new_str)
{
	free(*old);
	*old = new_str;
	return (1);
}
