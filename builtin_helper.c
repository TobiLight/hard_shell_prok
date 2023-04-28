/*
 * File: builtin_helper.c
 * Authors: Oluwatobiloba Light
 *          Princewill Chimdi Samuel
*/

#include "shell.h"

int shelly_cd_helper(char **, char *, struct stat);
int shelly_cd_helper2(char *, char *, char **);

/**
 * shelly_cd_helper - Helper function inside shelly_cd_helper
 * @args: A pointer to a pointer of array of arguments
 * @oldpwd: A pointer to old working directory
 * @dir: File system status
 *
 * Return: On success, zero is returned.
 *         On error, -1 is returned, and errno is set appropriately.
 */
int shelly_cd_helper(char **args, char *oldpwd, struct stat dir)
{
	if (args[0])
	{
		if (*(args[0]) == '-' || shelly_strcmp(args[0], "--") == 0)
		{
			if ((args[0][1] == '-' && args[0][2] == '\0') ||
				args[0][1] == '\0')
			{
				if (shelly_getenv("OLDPWD") != NULL)
					(chdir(*shelly_getenv("OLDPWD") + 7));
			}
			else
			{
				free(oldpwd);
				return (shelly_create_error(args, 2));
			}
		}
		else
		{
			if (stat(args[0], &dir) == 0 && S_ISDIR(dir.st_mode) &&
				((dir.st_mode & S_IXUSR) != 0))
			{
				chdir(args[0]);
			}
			else
			{
				free(oldpwd);
				return (shelly_create_error(args, 2));
			}
		}
	}
	else
	{
		if (shelly_getenv("HOME") != NULL)
			chdir(*(shelly_getenv("HOME")) + 5);
	}
}

/**
 * shelly_cd_helper2 - Helper function inside shelly_cd_helper
 * @pwd: Pointer to current working directory
 * @oldpwd: Pointer to previous working directory
 * @dir_info: Directory info
 *
 * Return: -1
 */
int shelly_cd_helper2(char *pwd, char *oldpwd, char **dir_info)
{
	pwd = getcwd(pwd, 0);
	if (pwd == NULL)
	{
		free(oldpwd);
		return (-1);
	}

	dir_info = malloc(sizeof(char *) * 2);
	if (dir_info == NULL)
	{
		free(oldpwd);
		free(pwd);
		return (-1);
	}

	dir_info[0] = "OLDPWD";
	dir_info[1] = oldpwd;
	if (shelly_setenv(dir_info, dir_info) == -1)
	{
		free(oldpwd);
		free(pwd);
		free(dir_info);
		return (-1);
	}

	dir_info[0] = "PWD";
	dir_info[1] = pwd;
	if (shelly_setenv(dir_info, dir_info) == -1)
	{
		free(oldpwd);
		free(pwd);
		free(dir_info);
		return (-1);
	}
}
