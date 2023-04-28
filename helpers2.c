/*
 * File: handlers1.c
 * Authors: Oluwatobiloba Light
 *          Princewill Chimdi Samuel
 */

#include "shell.h"

ssize_t shelly_get_new_len(char *);
void shelly_logical_ops(char *, ssize_t *);
void shelly_handle_line(char **, ssize_t);

/**
 * shelly_logical_ops - Checks a line for logical operators "||" or "&&".
 * @line: A pointer to the character to check in the line.
 * @new_len: Pointer to new_len in shelly_get_new_len function.
 *
 * Return: nothing
 */
void shelly_logical_ops(char *line, ssize_t *new_len)
{
	char prev = *(line - 1);
	char curr = *line;
	char next = *(line + 1);

	if (curr == '&')
	{
		if (next == '&' && prev != ' ')
			(*new_len)++;
		else if (prev == '&' && next != ' ')
			(*new_len)++;
	}
	else if (curr == '|')
	{
		if (next == '|' && prev != ' ')
			(*new_len)++;
		else if (prev == '|' && next != ' ')
			(*new_len)++;
	}
}

/**
 * shelly_handle_line - Parses input line and adds necessary spaces
 * @line: Pointer to input line
 * @read: Length of input line
 *
 * Description: This function inserts spaces to separate ";", "||", and "&&",
 *              and replaces "#" with '\0'
 * Return: nothing
 */
void shelly_handle_line(char **line, ssize_t read)
{
	char *old_line, *new_line;
	char prev, curr, next;
	size_t i, j;
	ssize_t new_len;

	new_len = shelly_get_new_len(*line);
	if (new_len == read - 1)
		return;
	new_line = malloc(new_len + 1);
	if (!new_line)
		return;
	i = 0, j = 0;
	old_line = *line;
	while (old_line[i])
	{
		curr = old_line[i];
		next = old_line[i + 1];
		if (i != 0)
		{
			prev = old_line[i - 1];
			if (curr == ';')
			{
				if (next == ';' && prev != ' ' && prev != ';')
				{
					new_line[j++] = ' ';
					new_line[j++] = ';';
					continue;
				}
				else if (prev == ';' && next != ' ')
				{
					new_line[j++] = ';';
					new_line[j++] = ' ';
					continue;
				}
				if (prev != ' ')
					new_line[j++] = ' ';
				new_line[j++] = ';';
				if (next != ' ')
					new_line[j++] = ' ';
				continue;
			}
			else if (curr == '&')
			{
				if (next == '&' && prev != ' ')
					new_line[j++] = ' ';
				else if (prev == '&' && next != ' ')
				{
					new_line[j++] = '&';
					new_line[j++] = ' ';
					continue;
				}
			}
			else if (curr == '|')
			{
				if (next == '|' && prev != ' ')
					new_line[j++] = ' ';
				else if (prev == '|' && next != ' ')
				{
					new_line[j++] = '|';
					new_line[j++] = ' ';
					continue;
				}
			}
		}
		else if (curr == ';')
		{
			if (i != 0 && old_line[i - 1] != ' ')
				new_line[j++] = ' ';
			new_line[j++] = ';';
			if (next != ' ' && next != ';')
				new_line[j++] = ' ';
			continue;
		}
		new_line[j++] = old_line[i];
		i++;
	}
	new_line[j] = '\0';
	free(*line);
	*line = new_line;
}

/**
 * shelly_get_new_len - Computes the new length of a line partitioned
 *               by ";", "||", "&&" or "#".
 * @line: A pointer to the line to check.
 *
 * Description: Shortens lines containing '#' comments with '\0'.
 *
 * Return: The new length of the line.
 */

ssize_t shelly_get_new_len(char *line)
{
	size_t i = 0;
	ssize_t new_len = 0;
	char curr, next;

	while (line[i])
	{
		curr = line[i];
		next = line[i + 1];
		if (curr == '#')
		{
			if (i == 0 || line[i - 1] == ' ')
			{
				line[i] = '\0';
				break;
			}
		}
		else if (i != 0)
		{
			if (curr == ';')
			{
				if (next == ';' && line[i - 1] != ' ' && line[i - 1] != ';')
				{
					new_len += 2;
					continue;
				}
				else if (line[i - 1] == ';' && next != ' ')
				{
					new_len += 2;
					continue;
				}
				if (line[i - 1] != ' ')
					new_len++;
				if (next != ' ')
					new_len++;
			}
			else
				shelly_logical_ops(&line[i], &new_len);
		}
		else if (curr == ';')
		{
			if (i != 0 && line[i - 1] != ' ')
				new_len++;
			if (next != ' ' && next != ';')
				new_len++;
		}
		new_len++;
		i++;
	}
	return (new_len);
}
