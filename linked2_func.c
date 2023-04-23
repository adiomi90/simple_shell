#include "main.h"

/**
 * add_node - adds a node at the start of a linked list
 * @head: head pointer
 * @str: string data of node
 * @num: node index
 * Return: number of elements
 */
list_t *add_node(list_t **head, const char *str, int num)
{
	list_t *new;

	if (!head)
		return (NULL);
	new = malloc(sizeof(list_t));
	if (!new)
		return (NULL);
	_memset((void *)new, 0, sizeof(list_t));
	new->num = num;
	if (str)
	{
		new->str = _strdup(str);
		if (!new->str)
		{
			free(new);
			return (NULL);
		}
	}
	new->next = *head;
	*head = new;
	return (new);
}

/**
 * add_node_end - adds node at the end of a linked list
 * @head: address of pointer to head node
 * @str: str data of node
 * @num: node index
 * Return: number of elements
 */
list_t *add_node_end(list_t **head, const char *str, int num)
{
	list_t *new, *current;

	if (!head)
		return (NULL);

	current = *head;
	new = malloc(sizeof(list_t));
	if (!new)
		return (NULL);
	_memset((void *)new, 0, sizeof(list_t));
	new->num = num;
	if (str)
	{
		new->str = _strdup(str);
		if (!new->str)
		{
			free(new);
			return (NULL);
		}
	}
	if (current)
	{
		while (current->next)
			current = current->next;
		current->next = new;
	}
	else
		*head = new;
	return (new);
}

/**
 * print_liststr - prints the string data of a linked list
 * @head: linked list
 * Return: number of elements
 */
size_t print_liststr(const list_t *head)
{
	size_t len = 0;

	while (head)
	{
		_puts(head->str ? head->str : "(nil)");
		_puts("\n");
		head = head->next;
		len++;
	}
	return (len);
}

/**
 * delete_node_index - deletes a node at an index
 * @head: head pointer
 * @index: index of node
 * Return: 1 on success, 0 otherwise
 */
int delete_node_index(list_t **head, unsigned int index)
{
	list_t *current, *prev;
	unsigned int i = 0;

	if (!head || !*head)
		return (0);
	current = *head;
	if (!index)
	{
		*head = (*head)->next;
		free(current->str);
		free(current);
		return (1);
	}
	while (current)
	{
		if (i == index)
		{
			prev->next = current->next;
			free(current->str);
			free(current);
			return (1);
		}
		i++;
		prev = current;
		current = current->next;
	}
	return (0);
}

/**
 * free_list - frees a linked list
 * @head: head pointer
 * Return: Nothing
 */
void free_list(list_t **head)
{
	list_t *current, *nex;

	if (!head || !*head)
		return;
	current = *head;
	while (current)
	{
		nex = current->next;
		free(current->str);
		free(current);
		current = nex;
	}
	*head = NULL;
}
