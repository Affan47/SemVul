jump_to_next_prep(void)
{
	unsigned char car;
	const char *line_start;

	for (;;)
	{
		line_start = source_ptr;

		for(;;)
		{
			car = get_char();
			if (!car)
				return;
			if (car == '\n' || !car || !isspace(car))
				break;
			source_ptr++;
		}

		if (car == '#')
		{
			source_ptr = line_start;
			return;
		}

		for(;;)
		{
			car = get_char();
			if (!car)
				return;
			source_ptr++;
			if (car == '\n')
				break;
		}

		add_pattern(RT_NEWLINE, comp->line);
		comp->line++;
	}
}
