pevent_save (char *fn)
{
	int fd, i;
	char buf[1024];

	if (!fn)
		fd = hexchat_open_file ("pevents.conf", O_CREAT | O_TRUNC | O_WRONLY,
									 0x180, XOF_DOMODE);
	else
		fd = hexchat_open_file (fn, O_CREAT | O_TRUNC | O_WRONLY, 0x180,
									 XOF_FULLPATH | XOF_DOMODE);
	if (fd == -1)
	{


		perror ("Error opening config file\n");
		return;
	}

	for (i = 0; i < NUM_XP; i++)
	{
		write (fd, buf, g_snprintf (buf, sizeof (buf),
										  "event_name=%s\n", te[i].name));
		write (fd, buf, g_snprintf (buf, sizeof (buf),
										  "event_text=%s\n\n", pntevts_text[i]));
	}

	close (fd);
}
