chanopt_save_one_channel (chanopt_in_memory *co, int fh)
{
	int i;
	char buf[256];
	guint8 val;

	snprintf (buf, sizeof (buf), "%s = %s\n", "network", co->network);
	write (fh, buf, strlen (buf));

	snprintf (buf, sizeof (buf), "%s = %s\n", "channel", co->channel);
	write (fh, buf, strlen (buf));

	i = 0;
	while (i < sizeof (chanopt) / sizeof (channel_options))
	{
		val = G_STRUCT_MEMBER (guint8, co, chanopt[i].offset);
		if (val != SET_DEFAULT)
		{
			snprintf (buf, sizeof (buf), "%s = %d\n", chanopt[i].name, val);
			write (fh, buf, strlen (buf));
		}
		i++;
	}
}
