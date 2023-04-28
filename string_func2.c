/*
 * File: string_func2.c
 * Authors: Oluwatobiloba Light
 *          Princewill Chimdi Samuel
 */

#include "shell.h"

char *shelly_strcpy(char *, const char *);
int shelly_strcmp(char *, char *);
int shelly_strspn(char *, char *);
/**
 * shelly_strcpy - Copy a string
 * @dest: The destination buffer
 * @src: The source string
 *
 * Return: A pointer to the destination buffer
 */
char *shelly_strcpy(char *dest, const char *src)
{
	size_t i;

	for (i = 0; src[i] != '\0'; i++)
		dest[i] = src[i];
	dest[i] = '\0';

	return (dest);
}

/**
 * shelly_strcmp - Compare two strings
 * @s1: The first string
 * @s2: The second string
 *
 * Return: An integer less than, equal to, or greater than zero if s1 is found,
 *         respectively, to be less than, to match, or be greater than s2
 */
int shelly_strcmp(char *s1, char *s2)
{
	while (*s1 && *s2 && *s1 == *s2)
	{
		s1++;
		s2++;
	}

	if (*s1 != *s2)
		return (*s1 - *s2);

	return (0);
}

/**
 * shelly_strspn - Get the length of a prefix substring
 * @s: The string to be scanned
 * @accept: The string containing the characters to match
 *
 * Return: The length of the initial portion of s that consists of only the
 *         characters in accept
 */
int shelly_strspn(char *s, char *accept)
{
	int bytes = 0;
	int i;

	while (*s)
	{
		for (i = 0; accept[i]; i++)
		{
			if (*s == accept[i])
			{
				bytes++;
				break;
			}
		}
		s++;
	}
	return (bytes);
}
