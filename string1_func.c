#include "main.h"

/**
 * _strlen - finds the length of a string
 * @str: string
 * Return: length of the string
 */
size_t _strlen(const char *str)
{
    size_t len = 0;

    if (!str)
        return (0);

    while (str[len])
        len++;
    return (len);
}

/**
 * _strstartswith - checks if a string starts with a prefix string
 * @haystack: string to search
 * @needle: prefix string
 * Return: pointer to the next char of string or NULL
 */
char *_strstartswith(const char *haystack, const char *needle)
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
char *_strcat(char *dest, const char *src)
{
    char *ptr = dest;

    while (*dest)
        dest++;

    while (*src)
        *dest++ = *src++;

    *dest = '\0';
    return (ptr);
}

/**
 * _strcpy - copies a string
 * @dest: destination string
 * @src: source string
 * Return: pointer to destination string
 */
char *_strcpy(char *dest, const char *src)
{
    size_t i;

    if (dest == src || src == NULL)
        return (dest);

    for (i = 0; src[i]; i++)
        dest[i] = src[i];

    dest[i] = '\0';
    return (dest);
}

/**
 * _strdup - duplicates a string
 * @str: string to duplicate
 * Return: pointer to the duplicate string
 */
char *_strdup(const char *str)
{
    size_t len;
    char *new_str;

    if (str == NULL)
        return (NULL);

    len = _strlen(str);

    new_str = malloc(sizeof(char) * (len + 1));
    if (new_str == NULL)
        return (NULL);

    _strcpy(new_str, str);

    return (new_str);
}
