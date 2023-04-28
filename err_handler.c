/*
 * File: env_handler.c
 * Authors: Oluwatobiloba Light
 *          Princewill Chimdi Samuel
 */

#include "shell.h"

/**
 * shelly_error_env - Creates an error message for shellby_env errors.
 * @args: An array of arguments passed to the command.
 *
 * Return: The error string.
 */
char *shelly_error_env(char **args)
{
	char *error, *history_str;
	int len;

	history_str = shelly_itoa(history);
	if (history_str == NULL)
		return (NULL);

	args--;
	len = shelly_strlen(name) + shelly_strlen(history_str) + shelly_strlen(args[0]) + 45;
	error = malloc(sizeof(char) * (len + 1));
	if (error == NULL)
	{
		free(history_str);
		return (NULL);
	}

	shelly_strcpy(error, name);
	shelly_strcat(error, ": ");
	shelly_strcat(error, history_str);
	shelly_strcat(error, ": ");
	shelly_strcat(error, args[0]);
	shelly_strcat(error, ": Unable to add/remove from environment\n");

	free(history_str);
	return (error);
}

/**
 * shelly_error_1 - Creates an error message for shellby_alias errors.
 * @args: An array of arguments passed to the command.
 *
 * Return: The error string.
 */
char *shelly_error_1(char **args)
{
	char *error;
	int length = 0;

	length += shelly_strlen(name) + shelly_strlen(args[0]) + 13;
	error = malloc(sizeof(char) * (length + 1));
	if (error == NULL)
		return (NULL);

	shelly_strcpy(error, "alias: ");
	shelly_strcat(error, args[0]);
	shelly_strcat(error, " not found\n");

	return (error);
}

/**
 * shelly_error_2_exit - Creates an error message for shellby_exit errors.
 * @args: An array of arguments passed to the command.
 *
 * Return: The error string.
 */
char *shelly_error_2_exit(char **args)
{
	char *error, *history_str;
	int len;

	history_str = shelly_itoa(history);
	if (history_str == NULL)
		return (NULL);

	len = shelly_strlen(name) + shelly_strlen(history_str) + shelly_strlen(args[0]) + 27;
	error = malloc(sizeof(char) * (len + 1));
	if (!error)
	{
		free(history_str);
		return (NULL);
	}

	shelly_strcpy(error, name);
	shelly_strcat(error, ": ");
	shelly_strcat(error, history_str);
	shelly_strcat(error, ": exit: Illegal number: ");
	shelly_strcat(error, args[0]);
	shelly_strcat(error, "\n");

	free(history_str);
	return (error);
}

/**
 * shelly_error_2_cd - Creates an error message for cd errors.
 * @args: An array of arguments passed to the command.
 *
 * Return: The error string.
 */
char *shelly_error_2_cd(char **args)
{
	char *error, *history_str;
	int len;

	history_str = shelly_itoa(history);
	if (history_str == NULL)
		return (NULL);

	len = shelly_strlen(name) + shelly_strlen(history_str) + shelly_strlen(args[0]) + 25;
	if (args[0][0] == '-')
		len += 15;
	error = malloc(sizeof(char) * (len + 1));
	if (!error)
	{
		free(history_str);
		return (NULL);
	}

	shelly_strcpy(error, name);
	shelly_strcat(error, ": ");
	shelly_strcat(error, history_str);
	if (args[0][0] == '-')
		shelly_strcat(error, ": cd: illegal option -- ");
	else
		shelly_strcat(error, ": cd: can't cd to ");
	shelly_strcat(error, args[0]);
	shelly_strcat(error, "\n");

	free(history_str);
	return (error);
}

/**
 * shelly_error_2_syntax - Creates an error message for syntax errors.
 * @args: An array of arguments passed to the command.
 *
 * Return: The error string.
 */
char *shelly_error_2_syntax(char **args)
{
	char *error, *history_str;
	int length;

	history_str = shelly_itoa(history);
	if (history_str == NULL)
		return (NULL);

	length = shelly_strlen(name) + shelly_strlen(history_str) + shelly_strlen(args[0]) + 33;
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
	shelly_strcat(error, ": Syntax error: \"");
	shelly_strcat(error, args[0]);
	shelly_strcat(error, "\" unexpected\n");

	free(history_str);
	return (error);
}
