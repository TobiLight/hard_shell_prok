/*
 * File: env_builtin.c
 * Auth: Oluwatobiloba Light
 *       Princewill Chimdi Samuel
 */

#include "shell.h"

/**
 * shellx_env - Prints the current environment.
 * @args: An array of arguments passed to the shell.
 * @front: A double pointer to the beginning of args.
 *
 * Return: If an error occurs - -1.
 *         Otherwise - 0.
 */
int shellx_env(char **args, char __attribute__((__unused__)) **front)
{
	int i;
	char nc = '\n';

	if (environ == NULL)
		return (-1);

	for (i = 0; environ[i]; i++)
	{
		write(STDOUT_FILENO, environ[i], shellx_strlen(environ[i]));
		write(STDOUT_FILENO, &nc, 1);
	}

	(void)args;
	return (0);
}

/**
 * shellx_setenv - Adds or modifies an environmental variable.
 * @args: An array of arguments passed to the shell.
 * @front: A double pointer to the beginning of args.
 *
 * Return: If an error occurs - -1.
 *         Otherwise - 0.
 */
int shellx_setenv(char **args, char __attribute__((__unused__)) **front)
{
	char **env_var = NULL, **new_environ, *new_value;
	size_t size;
	int i;

	if (args[0] == NULL || args[1] == NULL)
		return (shellx_create_error(args, -1));

	new_value = malloc(shellx_strlen(args[0]) + 1 + shellx_strlen(args[1]) + 1);
	if (new_value == NULL)
		return (shellx_create_error(args, -1));
	shellx_strcpy(new_value, args[0]);
	shellx_strcat(new_value, "=");
	shellx_strcat(new_value, args[1]);

	env_var = shellx_getenv(args[0]);
	if (env_var)
	{
		free(*env_var);
		*env_var = new_value;
		return (0);
	}
	for (size = 0; environ[size]; size++)
		;

	new_environ = malloc(sizeof(char *) * (size + 2));
	if (new_environ == NULL)
	{
		free(new_value);
		return (shellx_create_error(args, -1));
	}

	for (i = 0; environ[i]; i++)
		new_environ[i] = environ[i];

	free(environ);
	environ = new_environ;
	environ[i] = new_value;
	environ[i + 1] = NULL;

	return (0);
}

/**
 * shellx_unsetenv - Deletes an environmental variable from the PATH.
 * @args: An array of arguments passed to the shell.
 * @front: A double pointer to the beginning of args.
 *
 * Return: If an error occurs - -1.
 *         Otherwise - 0.
 */
int shellx_unsetenv(char **args, char __attribute__((__unused__)) **front)
{
	char **env_var, **new_environ;
	size_t size;
	int i, j;

	if (args[0] == NULL)
		return (shellx_create_error(args, -1));
	env_var = shellx_getenv(args[0]);
	if (env_var == NULL)
		return (0);

	for (size = 0; environ[size]; size++)
		;

	new_environ = malloc(sizeof(char *) * size);
	if (new_environ == NULL)
		return (shellx_create_error(args, -1));

	for (i = 0, j = 0; environ[i]; i++)
	{
		if (*env_var == environ[i])
		{
			free(*env_var);
			continue;
		}
		new_environ[j] = environ[i];
		j++;
	}
	free(environ);
	environ = new_environ;
	environ[size - 1] = NULL;

	return (0);
}
