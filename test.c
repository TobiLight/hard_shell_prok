ssize_t shelly_getline(char **lineptr, size_t *n, FILE *stream)
{
	static char buffer[120];
	static ssize_t buf_size = 0;
	ssize_t response = 0;
	char x = 'x';

	if (lineptr == NULL || n == NULL)
		return (-1);

	while (x != '\n')
	{
		if (buf_size == 0)
		{
			buf_size = read(STDIN_FILENO, buffer, sizeof(buffer));
			if (buf_size == -1)
				return (-1);
			if (buf_size == 0 && input == 0)
				return (-1);
		}

		x = buffer[0];
		buf_size--;
		for (ssize_t i = 0; i < buf_size; i++)
		{
			buffer[i] = buffer[i + 1];
		}

		if (x == '\n')
		{
			if (shelly_appoint_lineptr(lineptr, n, buffer, response + 1) == NULL)
				return (-1);
			response++;
			break;
		}
		else
		{
			if (shelly_realloc(lineptr, n, response, response + 1) == NULL)
				return (-1);
			(*lineptr)[response] = x;
			response++;
		}
	}

	return (response);
}
