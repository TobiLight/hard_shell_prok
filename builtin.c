/*
 * File: builtin.c
 * Auth: Oluwatobiloba Light
 *       Princewill Chimdi Samuel
 */

#include "shell.h"

/**
 * shelly_exit - Exits the shell.
 * @args: An array of arguments.
 * @front: A double pointer to the beginning of args.
 *
 * Return: If there are no arguments - -3.
 *         If the given exit value is invalid - 2.
 *         O/w - exits with the given status value.
 */
int shelly_exit(char **args, char **front)
{
	int i = 0, int_len = 10;
	unsigned int max = 1 << (sizeof(int) * 8 - 1), num = 0;

	if (args[0])
	{
		if (args[0][0] == '+')
		{
			i = 1;
			int_len++;
		}
		while (args[0][i])
		{
			if (i <= int_len && args[0][i] >= '0' && args[0][i] <= '9')
				num = (num * 10) + (args[0][i] - '0');
			else
				return (shelly_create_error(--args, 2));
			i++;
		}
	}
	else
	{
		return (-3);
	}

	if (num > max - 1)
		return (shelly_create_error(--args, 2));

	args -= 1;
	shelly_free_args(args, front);
	shelly_free_env();
	shelly_free_alias_list(aliases);
	exit(num);
}

/**
 * shelly_cd - Changes the current directory of the shellby process.
 * @args: An array of arguments.
 * @front: A double pointer to the beginning of args.
 *
 * Return: If the given string is not a directory - 2.
 *         If an error occurs - -1.
 *         Otherwise - 0.
 */
int shelly_cd(char **args, char __attribute__((__unused__)) **front)
{
	char **dir_info, *new_line = "\n";
	char *oldpwd = NULL, *pwd = NULL;
	struct stat dir;

	oldpwd = getcwd(oldpwd, 0);
	if (oldpwd == NULL)
		return (-1);

	shelly_cd_helper(args, oldpwd, dir);
	shelly_cd_helper2(pwd, oldpwd, dir_info);
	if (args[0] && args[0][0] == '-' && args[0][1] != '-')
	{
		write(STDOUT_FILENO, pwd, shelly_strlen(pwd));
		write(STDOUT_FILENO, new_line, 1);
	}
	free(oldpwd);
	free(pwd);
	free(dir_info);
	return (0);
}

/**
 * shelly_help - Displays information about shellby builtin commands.
 * @args: An array of arguments.
 * @front: A pointer to the beginning of args.
 *
 * Return: 0 on success, -1 on failure.
 */
int shelly_help(char **args, char __attribute__((__unused__)) **front)
{
	if (args[0] == NULL)
		shelly_help_all();
	else if (shelly_strcmp(args[0], "help") == 0)
		shelly_help_help();
	else if (shelly_strcmp(args[0], "cd") == 0)
		shelly_help_cd();
	else if (shelly_strcmp(args[0], "alias") == 0)
		shelly_help_alias();
	else if (shelly_strcmp(args[0], "exit") == 0)
		shelly_help_exit();
	else if (shelly_strcmp(args[0], "env") == 0)
		shelly_help_env();
	else if (shelly_strcmp(args[0], "setenv") == 0)
		shelly_help_setenv();
	else if (shelly_strcmp(args[0], "unsetenv") == 0)
		shelly_help_unsetenv();
	else
		write(STDERR_FILENO, name, shelly_strlen(name));

	return (0);
}

/**
 * shelly_get_builtin - Matches a command with a corresponding
 *               shelly builtin function.
 * @cmd: The command to match.
 *
 * Return: A function pointer to the corresponding builtin.
 */
int (*shelly_get_builtin(char *cmd))(char **args, char **front)
{
	int i;
	sh_builtin_t bf[] = {
		{"exit", shelly_exit},
		{"env", shelly_env},
		{"setenv", shelly_setenv},
		{"unsetenv", shelly_unsetenv},
		{"cd", shelly_cd},
		{"alias", shelly_alias},
		{"help", shelly_help},
		{NULL, NULL}};

	i = 0;
	while (bf[i].name)
	{

		if (shelly_strcmp(bf[i].name, cmd) == 0)
			break;
		i++;
	}
	return (bf[i].func);
}
