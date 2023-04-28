/*
 * File: string_func1.c
 * Authors: Oluwatobiloba Light
 *          Princewill Chimdi Samuel
 */

#include "shell.h"

char *shelly_strncat(char *dest, const char *src, size_t n);
char *shelly_strcat(char *dest, const char *src);
char *shelly_strchr(char *str, char c);
int shelly_strlen(const char *str);
int shelly_strncmp(const char *s1, const char *s2, size_t n);

/**
 * shelly_strlen - Returns length of a string
 * @str: Pointer to the string
 *
 * Return: The length of the string
 */

int shelly_strlen(const char *str)
{
	int len = 0;

	if (!str)
		return (len);

	while (str[len])
		len++;

	return (len);
}

/**
 * shelly_strncat - Concantenates two strings where n number
 *            of bytes are copied from the src
 * @dest: A pointer to the destination string
 * @src: A pointer to the source string
 * @n: n bytes to copy from src
 *
 * Return: A pointer to the destination string
 */

char *shelly_strncat(char *dest, const char *src, size_t n)
{
	size_t i;
	size_t len_of_dest = shelly_strlen(dest);

	for (i = 0; i < n && src[i] != '\0'; i++)
		dest[len_of_dest + i] = src[i];

	dest[len_of_dest + i] = '\0';
	return (dest);
}

/**
 * shelly_strcat - Concantenates two strings where n number
 *            of bytes are copied from the src
 * @dest: A pointer to the destination string
 * @src: A pointer to the source string
 *
 * Return: A pointer to the destination string
 */
char *shelly_strcat(char *dest, const char *src)
{
	char *destTemp;
	const char *srcTemp;

	destTemp = dest;
	srcTemp = src;

	while (*destTemp != '\0')
		destTemp++;

	while (*srcTemp != '\0')
		*destTemp++ = *srcTemp++;
	*destTemp = '\0';
	return (dest);
}

/**
 * shelly_strchr - Locate character in string
 * @str: The string to search
 * @c: The character to search for
 *
 * Return: Pointer to the first occurrence of the character c in
 *         the string str, or NULL if the character is not found
 */

char *shelly_strchr(char *str, char c)
{
	while (*str != '\0')
	{
		if (*str == c)
			return (str);
		str++;
	}

	return (NULL);
}

/**
 * shelly_strncmp - Compare two strings up to a given number of bytes
 * @s1: The first string
 * @s2: The second string
 * @n: The maximum number of bytes to compare
 *
 * Return: An integer less than, equal to, or greater than zero if the first n
 *         bytes of s1 is found, respectively, to be less than, to match, or be
 *         greater than the first n bytes of s2
 */
int shelly_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t i;

	for (i = 0; s1[i] && s2[i] && i < n; i++)
	{
		if (s1[i] > s2[i])
			return (s1[i] - s2[i]);
		else if (s1[i] < s2[i])
			return (s1[i] - s2[i]);
	}
	if (i == n)
		return (0);
	else
		return (-15);
}
