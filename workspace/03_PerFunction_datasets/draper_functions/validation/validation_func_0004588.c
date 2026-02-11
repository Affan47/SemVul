parse_sound_times(char *string, int min, int max)
{
	char *number;
	char *beg;
	char *end;
	int	begnr;
	int	endnr;
	int	i;

	if ((!string) || (strcmp(string, "!") == 0) || (strcmp(string, "-") == 0))
	{
		for (i = min; i <= max; i++)
		{
			sound_available_hours[i] = FALSE;
		}

		return;
	}

	if (strcmp(string, "*") == 0)
	{
		free(string);

		for (i = min; i <= max; i++)
		{
			sound_available_hours[i] = TRUE;
		}

		return;
	}

	number = strtok(string, ",;:");

	while (number)
	{
		beg = number;

		if ((end = index(number, '-')))
		{
			*end++ = '\0';
		}
		else end = beg;

		begnr = atoi(beg);
		endnr = atoi(end);

		if ((begnr >= min) && (begnr <= max) && (endnr >= min) && (endnr <= max))
		{
			if (endnr >= begnr)
			{
				for (i = begnr; i <= endnr; i++)
				{
					sound_available_hours[i] = TRUE;
				}
			}
			else log(LOG_ERR, "starttime must be lower than endtime.");
		}
		else log(LOG_ERR, "start- or endtime out of range.");

		number = strtok(NULL, ",;:");
	}

	free(string);
}
