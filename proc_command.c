/*
 * File: proc_file_command.c
 * Authors: Oluwatobiloba Light
 *          Princewill Chimdi Samuel
 */

#include "shell.h"

int shelly_cant_open(char *file_path);

/**
 * shelly_cant_open - Prints an error message for a file that can't be opened.
 *
 * @file_path: The path to the file that couldn't be opened.
 *
 * Return: Always returns 127.
 */
int shelly_cant_open(char *file_path)
{
	char *error_msg, *history_str;
	int len;

	history_str = shelly_itoa(history);
	if (!history_str)
		return (127);

	len = shelly_strlen(name) + shelly_strlen(history_str)
		+ shelly_strlen(file_path) + 16;
	error_msg = malloc(sizeof(char) * (len + 1));
	if (!error_msg)
	{
		free(history_str);
		return (127);
	}

	shelly_strcpy(error_msg, name);
	shelly_strcat(error_msg, ": ");
	shelly_strcat(error_msg, history_str);
	shelly_strcat(error_msg, ": Can't open ");
	shelly_strcat(error_msg, file_path);
	shelly_strcat(error_msg, "\n");

	free(history_str);
	write(STDERR_FILENO, error_msg, len);
	free(error_msg);
	return (127);
}

/**
 * shelly_proc_commands - Processes commands from a file.
 * @file_path: Path to the file.
 * @exec_ret: Pointer to return value of the last executed command.
 *
 * Return: If file couldn't be opened - 127.
 *         If malloc fails - -1.
 *         Otherwise the return value of the last command ran.
 */
int shelly_proc_commands(char *file_path, int *exec_ret)
{
	unsigned int old_size = 120;
	unsigned int line_size = 0;
	ssize_t file, b_read, i;
	char *line, **args, **beg_args;
	char buffer[120];
	int ret;

	history = 0;
	file = open(file_path, O_RDONLY);
	if (file == -1)
	{
		*exec_ret = shelly_cant_open(file_path);
		return (*exec_ret);
	}
	line = malloc(sizeof(char) * old_size);
	if (line == NULL)
		return (-1);
	do {
		b_read = read(file, buffer, 119);
		if (b_read == 0 && line_size == 0)
			return (*exec_ret);
		buffer[b_read] = '\0';
		line_size += b_read;
		line = shelly_realloc(line, old_size, line_size);
		shelly_strcat(line, buffer);
		old_size = line_size;
	} while (b_read);
	for (i = 0; line[i] == '\n'; i++)
		line[i] = ' ';
	for (; i < line_size; i++)
	{
		if (line[i] == '\n')
		{
			line[i] = ';';
			for (i += 1; i < line_size && line[i] == '\n'; i++)
				line[i] = ' ';
		}
	}
	shelly_replace_variable(&line, exec_ret);
	shelly_handle_line(&line, line_size);
	args = shelly_strtok(line, " ");
	free(line);
	if (!args)
		return (0);
	if (shelly_check_args(args) != 0)
	{
		*exec_ret = 2;
		shelly_free_args(args, args);
		return (*exec_ret);
	}
	beg_args = args;

	for (i = 0; args[i]; i++)
	{
		if (shelly_strncmp(args[i], ";", 1) == 0)
		{
			free(args[i]);
			args[i] = NULL;
			ret = shelly_call_args(args, beg_args, exec_ret);
			args = &args[++i];
			i = 0;
		}
	}
	ret = shelly_call_args(args, beg_args, exec_ret);
	free(beg_args);
	return (ret);
}
