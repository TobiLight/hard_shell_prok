/*
 * File: main.c
 * Authors: Oluwatobiloba Light
 *          Princewill Chimdi Samuel
 */

#include "shell.h"

void shelly_sig_handler(int);
int shelly_execute(char **, char **);

/**
 * shelly_sig_handler - Prints a new prompt upon a signal.
 * @sig: The signal.
 *
 * Return: nothing
 */
void shelly_sig_handler(int sig)
{
	char *new_prompt = "\n$ ";

	(void)sig;
	signal(SIGINT, shelly_sig_handler);
	write(STDIN_FILENO, new_prompt, 3);
}

/**
 * shelly_execute - Executes a command in a child process.
 * @args: An array of arguments.
 * @front: A double pointer to the beginning of args.
 *
 * Return: If an error occurs - a corresponding error code.
 *         O/w - The exit value of the last executed command.
 */
int shelly_execute(char **args, char **front)
{
	pid_t child_pid;
	int status, flag = 0, ret = 0;
	char *cmd = args[0];

	if (cmd[0] != '/' && cmd[0] != '.')
	{
		flag = 1;
		cmd = shelly_get_loc(cmd);
	}

	if (cmd == NULL || (access(cmd, F_OK) == -1) || (access(cmd, X_OK) != 0))
	{
		if (errno == EACCES)
			ret = (shelly_create_error(args, 126));
		else
			ret = (shelly_create_error(args, 127));
	}
	else
	{
		child_pid = fork();
		if (child_pid == -1)
		{
			if (flag)
				free(cmd);
			perror("Error child:");
			return (1);
		}
		if (child_pid == 0)
		{
			execve(cmd, args, environ);
			if (errno == EACCES)
				ret = (shelly_create_error(args, 126));
			shelly_free_env();
			shelly_free_args(args, front);
			shelly_free_alias_list(aliases);
			_exit(ret);
		}
		else
		{
			wait(&status);
			ret = WEXITSTATUS(status);
		}
	}
	if (flag)
		free(cmd);
	return (ret);
}

/**
 * main - Runs a simple UNIX command interpreter.
 * @argc: The number of arguments supplied to the program.
 * @argv: An array of pointers to the arguments.
 *
 * Return: The return value of the last executed command.
 */
int main(int argc, char *argv[])
{
	int ret = 0, retn, *exec_ret = &retn;
	char *prompt = "$ ", *new_line = "\n";

	name = argv[0];
	history = 1;
	aliases = NULL;
	signal(SIGINT, shelly_sig_handler);
	*exec_ret = 0;
	environ = shelly_copyenv();
	if (environ == NULL)
		exit(-100);

	if (argc != 1)
	{
		ret = shelly_proc_commands(argv[1], exec_ret);
		shelly_free_env();
		shelly_free_alias_list(aliases);
		return (*exec_ret);
	}
	if (!isatty(STDIN_FILENO))
	{
		while (ret != SHELLY_END_OF_FILE && ret != SHELLY_EXIT)
			ret = shelly_handle_args(exec_ret);
		shelly_free_env();
		shelly_free_alias_list(aliases);
		return (*exec_ret);
	}
	while (1)
	{
		write(STDOUT_FILENO, prompt, 2);
		ret = shelly_handle_args(exec_ret);
		if (ret == SHELLY_END_OF_FILE || ret == SHELLY_EXIT)
		{
			if (ret == SHELLY_END_OF_FILE)
				write(STDOUT_FILENO, new_line, 1);
			shelly_free_env();
			shelly_free_alias_list(aliases);
			exit(*exec_ret);
		}
	}
	shelly_free_env();
	shelly_free_alias_list(aliases);
	return (*exec_ret);
}
