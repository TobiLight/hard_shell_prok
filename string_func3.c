/*
 * File: string_func3.c
 * Auth: Alex Yu
 *       Brennan D Baraban
 */

#include "shell.h"

int shelly_token_len(char *str, char *delim);
int shelly_token_count(char *str, char *delim);
char **shelly_strtok(char *str, char *delim);

/**
 * shelly_token_len - Locates the delimiter i marking the end
 *             of the first token contained within a string.
 * @str: The string to be searched.
 * @delim: The delimiter character.
 *
 * Return: The delimiter index marking the end of
 *         the intitial token pointed to be str.
 */
int shelly_token_len(char *str, char *delim)
{
	int i = 0, len = 0;

	while (*(str + i) && *(str + i) != *delim)
	{
		len++;
		i++;
	}

	return (len);
}

/**
 * shelly_token_count - Counts the number of delimited
 *                words contained within a string.
 * @str: The string to be searched.
 * @delim: The delimiter character.
 *
 * Return: The number of words contained within str.
 */
int shelly_token_count(char *str, char *delim)
{
	int i, tokens = 0, len = 0;

	for (i = 0; *(str + i); i++)
		len++;

	for (i = 0; i < len; i++)
	{
		if (*(str + i) != *delim)
		{
			tokens++;
			i += shelly_token_len(str + i, delim);
		}
	}

	return (tokens);
}

/**
 * shelly_strtok - parses a string into a sequence of tokens
 * @str: Pointer to the string to be parsed
 * @delim: Pointer to bytes that delimits tokens in the parsed string
 *
 * Return: Pointer to the next token or NULL if no tokens
 */

char **shelly_strtok(char *str, char *delim)
{
	char **ptr;
	int i = 0, tokens, t, letters, l;

	tokens = shelly_token_count(str, delim);
	if (tokens == 0)
		return (NULL);

	ptr = malloc(sizeof(char *) * (tokens + 2));
	if (ptr == NULL)
		return (NULL);

	for (t = 0; t < tokens; t++)
	{
		while (str[i] == *delim)
			i++;

		letters = shelly_token_len(str + i, delim);
		ptr[t] = malloc(sizeof(char) * (letters + 1));
		if (!ptr[t])
		{
			for (i -= 1; i >= 0; i--)
				free(ptr[i]);
			free(ptr);
			return (NULL);
		}

		for (l = 0; l < letters; l++)
		{
			ptr[t][l] = str[i];
			i++;
		}

		ptr[t][l] = '\0';
	}
	ptr[t] = NULL;
	ptr[t + 1] = NULL;

	return (ptr);
}
