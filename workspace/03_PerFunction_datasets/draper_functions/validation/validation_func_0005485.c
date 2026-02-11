gets_fromFile(FILE *source)
{
	static PQExpBuffer buffer = NULL;

	char		line[1024];

	if (buffer == NULL)
		buffer = createPQExpBuffer();
	else
		resetPQExpBuffer(buffer);

	for (;;)
	{
		char	   *result;


		sigint_interrupt_enabled = true;


		result = fgets(line, sizeof(line), source);


		sigint_interrupt_enabled = false;


		if (result == NULL)
			break;

		appendPQExpBufferStr(buffer, line);


		if (buffer->data[buffer->len - 1] == '\n')
		{
			buffer->data[buffer->len - 1] = '\0';
			return pg_strdup(buffer->data);
		}
	}

	if (buffer->len > 0)
		return pg_strdup(buffer->data);


	return NULL;
}
