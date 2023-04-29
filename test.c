ssize_t shelly_getline(char **lineptr, size_t *n, FILE *stream)
{
	static ssize_t input;
	ssize_t response;
	static char *buffer[SHELLY_READ_BUF_SIZE], x = 'x';
	int r;

	if (input == 0)
		fflush(stream);
	else
		return (-1);
	input = 0;

	while (x != '\n')
	{
		r = read(STDIN_FILENO, &x, 1);
		if (r == -1 || (r == 0 && input == 0))
		{
			free(buffer);
			return (-1);
		}
		if (r == 0 && input != 0)
		{
			input++;
			break;
		}

		if (input >= SHELLY_READ_BUF_SIZE)
			buffer = shelly_realloc(buffer, input, input + 1);

		buffer[input] = x;
		input++;
	}
	buffer[input] = '\0';
	shelly_appoint_lineptr(lineptr, n, buffer, input);
	response = input;
	if (r != 0)
		input = 0;
	return (response);
}
