get_exec_time(void)
{
	static gchar timestr[30];
	static struct timeval start_tv = {0, 0};
	static struct timeval previous = {0, 0};
	static gint started = 0;

	struct timeval tv = {0, 0};
	static struct timeval delta = {0, 0};

	gettimeofday(&tv, NULL);

	if (start_tv.tv_sec == 0) start_tv = tv;

	tv.tv_sec -= start_tv.tv_sec;
	if (tv.tv_usec >= start_tv.tv_usec)
		tv.tv_usec -= start_tv.tv_usec;
	else
		{
		tv.tv_usec += 1000000 - start_tv.tv_usec;
		tv.tv_sec -= 1;
		}

	if (started) timeval_delta(&delta, &tv, &previous);

	previous = tv;
	started = 1;

	g_snprintf(timestr, sizeof(timestr), "%5d.%06d (+%05d.%06d)", (gint)tv.tv_sec, (gint)tv.tv_usec, (gint)delta.tv_sec, (gint)delta.tv_usec);

	return timestr;
}
