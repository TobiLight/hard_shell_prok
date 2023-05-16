/*
 * File: env_handler.c
 * Auth: Oluwatobiloba Light
 *       Princewill Chimdi Samuel
 */

#include "shellx.h"

/**
 * shelly_copyenv - Creates a copy of the environment.
 *
 * Return: On success, a pointer to the new copy of the environment,
 *         otherwise NULL.
 */
char **shelly_copyenv(void)
{
	char **new_environ;
	size_t size;
	int i;

	for (size = 0; environ[size]; size++)
		;

	new_environ = malloc(sizeof(char *) * (size + 1));
	if (new_environ == NULL)
		return (NULL);

	for (i = 0; environ[i]; i++)
	{
		new_environ[i] = malloc(shelly_strlen(environ[i]) + 1);
		if (new_environ[i] == NULL)
		{
			for (i--; i >= 0; i--)
				free(new_environ[i]);
			free(new_environ);
			return (NULL);
		}
		shelly_strcpy(new_environ[i], environ[i]);
	}
	new_environ[i] = NULL;

	return (new_environ);
}

/**
 * shelly_getenv - Gets an environmental variable from the PATH.
 * @var: The name of the environmental variable to get.
 *
 * Return: If the environmental variable does not exist - NULL.
 *         Otherwise - a pointer to the environmental variable.
 */
char **shelly_getenv(const char *var)
{
	int i, length;

	length = shelly_strlen(var);
	for (i = 0; environ[i]; i++)
	{
		if (shelly_strncmp(var, environ[i], length) == 0)
			return (&environ[i]);
	}

	return (NULL);
}

/**
 * shelly_free_env - Frees the the environment copy.
 */
void shelly_free_env(void)
{
	int i;

	for (i = 0; environ[i]; i++)
		free(environ[i]);
	free(environ);
}
