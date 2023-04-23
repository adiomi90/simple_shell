#include "main.h"

/**
 * free_buff - frees a buffer pointer and set it to NULLs
 * @ptr: address of buffer pointer
 * Return: 1 on success, otherwise 0.
 */
int free_buff(void **ptr)
{
	if (ptr && *ptr)
	{
		free(*ptr);
		*ptr = NULL;
		return (1);
	}
	return (0);
}


/**
 **_memset - initialises memory space with a constant byte
 *@s: the pointer to the memory area
 *@b: the byte for initialisation
 *@n: the amount of bytes to be filled
 *Return: a pointer to the string
 */
char *_memset(char *s, char b, unsigned int n)
{
	unsigned int i;

	for (i = 0; i < n; i++)
		s[i] = b;
	return (s);
}

/**
 * free_str - frees an array of strings
 * @ptr: an of strings
 */
void free_str(char **ptr)
{
	char **str = ptr;

	if (!ptr)
		return;
	while (*ptr)
	{
		free(*ptr);
		ptr++;
	}
	free(str);
}

/**
 * _realloc - reallocates a block of memory
 * @ptr: pointer to previous malloc'ated block
 * @old_size: byte size of previous block
 * @new_size: byte size of new block
 * Return: pointer to the new memory block.
 */
void *_realloc(void *ptr, unsigned int old_size, unsigned int new_size)
{
	char *_p;

	if (!ptr)
		return (malloc(new_size));
	if (!new_size)
		return (free(ptr), NULL);
	if (new_size == old_size)
		return (ptr);

	_p = malloc(new_size);
	if (!_p)
		return (NULL);

	old_size = old_size < new_size ? old_size : new_size;
	while (old_size--)
		_p[old_size] = ((char *)ptr)[old_size];
	free(ptr);
	return (_p);
}
