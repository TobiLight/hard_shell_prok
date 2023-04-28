/*
 * File: err_handler2.c
 * Authors: Oluwatobiloba Light
 *          Princewill Chimdi Samuel
 */

#include "shell.h"

/**
 * shelly_error_126 - Creates an error message for permission denied failures.
 * @args: An array of arguments passed to the command.
 *
 * Return: The error string.
 */
char *shelly_error_126(char **args)
{
	char *error, *history_str;
	int length;

	history_str = shelly_itoa(history);
	if (history_str == NULL)
		return (NULL);

	length = shelly_strlen(name) + shelly_strlen(history_str)
		+ shelly_strlen(args[0]) + 24;
	error = malloc(sizeof(char) * (length + 1));
	if (!error)
	{
		free(history_str);
		return (NULL);
	}

	shelly_strcpy(error, name);
	shelly_strcat(error, ": ");
	shelly_strcat(error, history_str);
	shelly_strcat(error, ": ");
	shelly_strcat(error, args[0]);
	shelly_strcat(error, ": Permission denied\n");

	free(history_str);
	return (error);
}

/**
 * shelly_error_127 - Creates an error message for command not found failures.
 * @args: An array of arguments passed to the command.
 *
 * Return: The error string.
 */
char *shelly_error_127(char **args)
{
	char *error, *history_str;
	int length;

	history_str = shelly_itoa(history);
	if (history_str == NULL)
		return (NULL);

	length = shelly_strlen(name) + shelly_strlen(history_str)
		+ shelly_strlen(args[0]) + 16;
	error = malloc(sizeof(char) * (length + 1));
	if (!error)
	{
		free(history_str);
		return (NULL);
	}

	shelly_strcpy(error, name);
	shelly_strcat(error, ": ");
	shelly_strcat(error, history_str);
	shelly_strcat(error, ": ");
	shelly_strcat(error, args[0]);
	shelly_strcat(error, ": not found\n");

	free(history_str);
	return (error);
}
