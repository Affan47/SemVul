create_command_generator(const char *text, int state)
{
	static int	list_index,
				string_length;
	const char *name;


	if (state == 0)
	{
		list_index = 0;
		string_length = strlen(text);
	}


	while ((name = words_after_create[list_index++].name))
	{
		if ((pg_strncasecmp(name, text, string_length) == 0) && !words_after_create[list_index - 1].noshow)
			return pg_strdup(name);
	}

	return NULL;
}
