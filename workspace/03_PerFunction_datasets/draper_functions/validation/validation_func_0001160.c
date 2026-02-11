calc_timeout()
{
    static timeval sleep_interval;

    if (ntasks)
    {
	timeval wake_time;
	if (recurring_proc)
	    wake_time = next_task_time;
	if (!recurring_proc || first_task && first_task->when < wake_time)
	    wake_time = first_task->when;
	timeval now;
	(void) gettimeofday(&now, NULL);
	sleep_interval = wake_time - now;
	if (sleep_interval.tv_sec < 0)
	    timerclear(&sleep_interval);
	return &sleep_interval;
    }
    else
	return NULL;
}
