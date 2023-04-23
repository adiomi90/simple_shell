#include "main.h"

/**
 * _strlen - finds the length of a string
 * @str: string
 * Return: length of the string
 */
int _strlen(char *str)
{
	int len = 0;

	if (!str)
		return (0);

	while (*str++)
		len++;
	return (len);
}

/**
 * _strstart - checks if a string starts with a prefix string
 * @haystack: string to search
 * @needle: prefix string
 * Return: pointer to the next char of string or NULL
 */
char *_strstart(const char *haystack, const char *needle)
{
	while (*needle)
		if (*needle++ != *haystack++)
			return (NULL);
	return ((char *)haystack);
}

/**
 * _strcat - concatenates two strings
 * @dest: destination string
 * @src: source string
 * Return: pointer to destination string
 */
char *_strcat(char *dest, char *src)
{
	char *str = dest;

	while (*dest)
		dest++;
	while (*src)
		*dest++ = *src++;
	*dest = *src;
	return (str);
}

/**
 * _strcpy - copies a string
 * @dest: destination string
 * @src: source string
 * Return: pointer to destination string
 */
char *_strcpy(char *dest, char *src)
{
	int j = 0;

	if (dest == src || src == 0)
		return (dest);
	while (src[j])
	{
		dest[j] = src[j];
		j++;
	}
	dest[j] = 0;
	return (dest);
}

/**
 * _strdup - duplicates a string
 * @str: string to duplicate
 * Return: pointer to the duplicate string
 */
char *_strdup(const char *str)
{
	int len = 0;
	char *dest;

	if (str == NULL)
		return (NULL);
	while (*str++)
		len++;
	dest = malloc(sizeof(char) * (len + 1));
	if (!dest)
		return (NULL);
	for (len++; len--;)
		dest[len] = *--str;
	return (dest);
}

