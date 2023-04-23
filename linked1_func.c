#include "main.h"

/**
 * list_len - finds the length of a linked list
 * @head: linked list
 * Return: number of elements
 */
size_t list_len(const list_t *head)
{
	size_t len = 0;

	while (head)
	{
		head = head->next;
		len++;
	}
	return (len);
}

/**
 * str_from_list - returns the string data of a linked list
 * @head: linked list
 * Return: string data
 */
char **str_from_list(list_t *head)
{
	list_t *current = head;
	size_t len = list_len(head), i, j;
	char **strs;
	char *ptr;

	if (!head || !len)
		return (NULL);
	strs = malloc(sizeof(char *) * (len + 1));
	if (!strs)
		return (NULL);
	for (i = 0; current; current = current->next, i++)
	{
		ptr = malloc(_strlen(current->str) + 1);
		if (!ptr)
		{
			for (j = 0; j < i; j++)
				free(strs[j]);
			free(strs);
			return (NULL);
		}

		ptr = _strcpy(ptr, current->str);
		strs[i] = ptr;
	}
	strs[i] = NULL;
	return (strs);
}


/**
 * print_list - prints all elements of a linked list
 * @head: linked list
 * Return: number of elements
 */
size_t print_list(const list_t *head)
{
	size_t len = 0;

	while (head)
	{
		_puts(_convert_num(head->num, 10, 0));
		_putchar(':');
		_putchar(' ');
		_puts(head->str ? head->str : "(nil)");
		_puts("\n");
		head = head->next;
		len++;
	}
	return (len);
}

/**
 * node_strstart - returns node starting with a prefix string
 * @head: linked list
 * @pstr: prefix string
 * @c: next char after prefix string
 * Return: matched node or null
 */
list_t *node_strstart(list_t *head, char *pstr, char c)
{
	char *ptr = NULL;

	while (head)
	{
		ptr = _strstart(head->str, pstr);
		if (ptr && ((c == -1) || (*ptr == c)))
			return (head);
		head = head->next;
	}
	return (NULL);
}

/**
 * get_node_index - returns the index of a node
 * @head: linked list
 * @current: pointer to the node
 * Return: index of node, -1 on failure
 */
ssize_t get_node_index(list_t *head, list_t *current)
{
	size_t index = 0;

	while (head)
	{
		if (head == current)
			return (index);
		head = head->next;
		index++;
	}
	return (-1);
}
