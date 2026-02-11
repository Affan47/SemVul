keep_alive()
{
	if (!enabled)
		return;

	unsigned long cur = CL_System::get_time();
	if (last_time > cur)
		last_time = cur;

	while (cur >= last_time + interval)
	{
		sig_timer()();
		last_time += interval;
	}
}
