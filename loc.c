/*
 * File: loc.c
 * Authors: Oluwatobiloba Light
 *          Princewill Chimdi Samuel
 */

#include "shell.h"

char *shelly_fill_path_dir(char *);
sh_singly_list_t *shelly_get_path_dir(char *);

/**
 * shelly_get_loc - Locates a command in the PATH.
 * @cmd: The command to locate.
 *
 * Return: If an error occurs or the command cannot be located - NULL.
 *         Otherwise - the full pathname of the command.
 */
char *shelly_get_loc(char *cmd)
{
	char **path, *temp;
	sh_singly_list_t *directories, *head;
	struct stat st;

	path = shelly_getenv("PATH");
	if (path == NULL || (*path) == NULL)
		return (NULL);

	directories = shelly_get_path_dir(*path + 5);
	head = directories;
	while (directories)
	{
		temp = malloc(shelly_strlen(directories->dir) + shelly_strlen(cmd) + 2);
		if (!temp)
			return (NULL);

		shelly_strcpy(temp, directories->dir);
		shelly_strcat(temp, "/");
		shelly_strcat(temp, cmd);

		if (stat(temp, &st) == 0)
		{
			shelly_free_list(head);
			return (temp);
		}
		directories = directories->next;
		free(temp);
	}
	shelly_free_list(head);
	return (NULL);
}

/**
 * shelly_fill_path_dir - Copies path and also replaces
 *                        leading/sandwiched/trailing colons (:)
 *                        with current working directory.
 * @path: The colon-separated list of directories.
 *
 * Return: A copy of path with any leading/sandwiched/trailing
 *         colons replaced with the current working directory.
 */
char *shelly_fill_path_dir(char *path)
{
	int i, length = 0;
	char *path_cpy, *pwd;

	pwd = *(shelly_getenv("PWD")) + 4;
	i = 0;
	while (path[i])
	{
		if (path[i] == ':')
		{
			if (path[i + 1] == ':' || i == 0 || path[i + 1] == '\0')
				length += shelly_strlen(pwd) + 1;
			else
				length++;
		}
		else
			length++;
		i++;
	}
	path_cpy = malloc(sizeof(char) * (length + 1));
	if (path_cpy == NULL)
		return (NULL);
	path_cpy[0] = '\0';
	i = 0;
	while (path[i])
	{
		if (path[i] == ':')
		{
			if (i == 0)
			{
				shelly_strcat(path_cpy, pwd);
				shelly_strcat(path_cpy, ":");
			}
			else if (path[i + 1] == ':' || path[i + 1] == '\0')
			{
				shelly_strcat(path_cpy, ":");
				shelly_strcat(path_cpy, pwd);
			}
			else
				shelly_strcat(path_cpy, ":");
		}
		else
		{
			shelly_strncat(path_cpy, &path[i], 1);
		}
		i++;
	}
	return (path_cpy);
}

/**
 * shelly_get_path_dir - Tokenizes a colon-separated list of
 *                directories into a sh_singly_list_T linked list.
 * @path: The colon-separated list of directories.
 *
 * Return: A pointer to the initialized linked list.
 */
sh_singly_list_t *shelly_get_path_dir(char *path)
{
	int i;
	char **directories, *path_cpy;
	sh_singly_list_t *head = NULL;

	path_cpy = shelly_fill_path_dir(path);
	if (path_cpy == NULL)
		return (NULL);
	directories = shelly_strtok(path_cpy, ":");
	free(path_cpy);
	if (!directories)
		return (NULL);
	i = 0;
	while (directories[i])
	{
		if (shelly_add_node_end(&head, directories[i]) == NULL)
		{
			shelly_free_list(head);
			free(directories);
			return (NULL);
		}
		i++;
	}
	free(directories);
	return (head);
}
