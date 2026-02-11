tty_write(char *buf, int len)
{
	int in_esc = 0;
	int esc_state = 0;

	if (discard)
		return len;


	if (len == 1 && *buf == 0)
		return len;


	if (len == 1 && buf[0] == '\f')
	{
		last_char = '\f';
		return write(termfd, "\033[H\033[2J", 7);
	}

	if (debug & DEBUG_FLAG_TTY2)
	{
		int i;
		DEBUG_TTY2("Printing %d: ", len);
		for (i=0; i<len; i++)
		{
			if (isgraph(buf[i]))
			{
				DEBUGLOG(DEBUG_FLAG_TTY2,  "%d: %c ", i, buf[i]);
			}
			else
			{
				DEBUGLOG(DEBUG_FLAG_TTY2,  "%d: 0x%02x ", i, (unsigned char)buf[i]);
			}
		}
		DEBUGLOG(DEBUG_FLAG_TTY2, "\n");
	}

	write(termfd, buf, len);

	if (len)
	{


		if (!interpret_escape)
		{
			int i;
			for (i=0; i<len; i++)
			{
				if (buf[i] == ESC)
					in_esc = 1;
				else
				{
					if (!in_esc && buf[i])
						last_char = buf[i];
					if (in_esc && !parse_escape(buf[i], &esc_state))
						in_esc = 0;
				}
			}
		}
		else
		{
			last_char = buf[len-1];
		}

		DEBUG_TTY("Setting last_char to %02x, interpret_escape=%d\n", last_char, interpret_escape);
	}
	return len;
}
