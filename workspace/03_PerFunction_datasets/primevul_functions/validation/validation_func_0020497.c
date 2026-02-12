static int mt_compute_timestamp(struct mt_application *app, __s32 value)
{
	long delta = value - app->prev_scantime;
	unsigned long jdelta = jiffies_to_usecs(jiffies - app->jiffies);

	app->jiffies = jiffies;

	if (delta < 0)
		delta += app->scantime_logical_max;


	delta *= 100;

	if (jdelta > MAX_TIMESTAMP_INTERVAL)

		return 0;
	else
		return app->timestamp + delta;
}
