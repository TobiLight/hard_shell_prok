/*
 * File: input_handlers.c
 * Authors: Oluwatobiloba Light
 *          Princewill Chimdi Samuel
 */

#include "shell.h"

/**
 * shelly_handle_args - Gets, calls, and runs the execution of a command.
 * @exe_ret: The return value of the parent process' last executed command.
 *
 * Return: If an end-of-file is read - END_OF_FILE (-2).
 *         If the input cannot be tokenized - -1.
 *         O/w - The exit value of the last executed command.
 */
int shelly_handle_args(int *exe_ret)
{
	int ret = 0, i;
	char *line = NULL, **args, **beg_arg;

	line = shelly_get_args(line, exe_ret);
	if (line == NULL)
		return (SHELLY_END_OF_FILE);

	args = shelly_strtok(line, " ");
	free(line);
	if (args == NULL)
		return (ret);
	if (shelly_check_args(args) != 0)
	{
		*exe_ret = 2;
		shelly_free_args(args, args);
		return (*exe_ret);
	}
	beg_arg = args;

	for (i = 0; args[i]; i++)
	{
		if (shelly_strncmp(args[i], ";", 1) == 0)
		{
			free(args[i]);
			args[i] = NULL;
			ret = shelly_call_args(args, beg_arg, exe_ret);
			args = &args[++i];
			i = 0;
		}
	}
	if (args)
		ret = shelly_call_args(args, beg_arg, exe_ret);

	free(beg_arg);
	return (ret);
}

/**
 * shelly_get_args - Gets a command from standard input.
 * @line: A buffer to store the command.
 * @exe_ret: The return value of the last executed command.
 *
 * Return: If an error occurrs - NULL.
 *         Otherwise - a pointer to the stored command.
 */
char *shelly_get_args(char *line, int *exe_ret)
{
	size_t size = 0;
	ssize_t read;
	char *prompt = "";

	if (line)
		free(line);

	read = shelly_getline(&line, &size, STDIN_FILENO);
	if (read == -1)
		return (NULL);
	if (read == 1)
	{
		history++;
		if (isatty(STDIN_FILENO))
			write(STDOUT_FILENO, prompt, 2);
		return (shelly_get_args(line, exe_ret));
	}

	line[read - 1] = '\0';
	shelly_replace_variable(&line, exe_ret);
	shelly_handle_line(&line, read);

	return (line);
}

/**
 * shelly_call_args - Partitions operators from commands and calls them.
 * @args: An array of arguments.
 * @beg_arg: A double pointer to the beginning of args.
 * @exe_ret: The return value of the parent process' last executed command.
 *
 * Return: The return value of the last executed command.
 */
int shelly_call_args(char **args, char **beg_arg, int *exe_ret)
{
	int ret = 0, i;

	if (args[0] == NULL)
		return (*exe_ret);
	for (i = 0; args[i]; i++)
	{
		if (shelly_strncmp(args[i], "||", 2) == 0)
		{
			free(args[i]);
			args[i] = NULL;
			args = shelly_replace_aliases(args);
			ret = shelly_run_args(args, beg_arg, exe_ret);
			if (*exe_ret != 0)
			{
				args = &args[++i];
				i = 0;
			}
			else
			{
				for (i++; args[i]; i++)
					free(args[i]);
				return (ret);
			}
		}
		else if (shelly_strncmp(args[i], "&&", 2) == 0)
		{
			free(args[i]);
			args[i] = NULL;
			args = shelly_replace_aliases(args);
			ret = shelly_run_args(args, beg_arg, exe_ret);
			if (*exe_ret == 0)
			{
				args = &args[++i];
				i = 0;
			}
			else
			{
				for (i++; args[i]; i++)
					free(args[i]);
				return (ret);
			}
		}
	}
	args = shelly_replace_aliases(args);
	ret = shelly_run_args(args, beg_arg, exe_ret);
	return (ret);
}

/**
 * shelly_run_args - Calls the execution of a command.
 * @args: An array of arguments.
 * @beg_arg: A double pointer to the beginning of args.
 * @exe_ret: The return value of the parent process' last executed command.
 *
 * Return: The return value of the last executed command.
 */
int shelly_run_args(char **args, char **beg_arg, int *exe_ret)
{
	int ret, i;
	int (*builtin)(char **args, char **beg_arg);

	builtin = shelly_get_builtin(args[0]);
	if (builtin)
	{
		ret = builtin(args + 1, beg_arg);
		if (ret != SHELLY_EXIT)
			*exe_ret = ret;
	}
	else
	{
		*exe_ret = shelly_execute(args, beg_arg);
		ret = *exe_ret;
	}
	history++;
	for (i = 0; args[i]; i++)
		free(args[i]);

	return (ret);
}

/**
 * shelly_check_args - Check for leading semicolons, ampersands, or pipes.
 *
 * @args: An array of arguments to check.
 *
 * Return: 0 if no invalid sequences are found, otherwise 2.
 */
int shelly_check_args(char **args)
{
	size_t i = 0;
	char *current, *next;

	while (args[i])
	{
		current = args[i];
		if (current[0] == ';' || current[0] == '&' || current[0] == '|')
		{
			if (i == 0 || current[1] == ';')
				return (shelly_create_error(&args[i], 2));
			next = args[i + 1];
			if (next && (next[0] == ';' || next[0] == '&' || next[0] == '|'))
				return (shelly_create_error(&args[i + 1], 2));
		}
		i++;
	}
	return (0);
}
