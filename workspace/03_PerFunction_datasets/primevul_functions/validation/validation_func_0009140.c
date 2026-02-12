static void tty_update_time(struct timespec64 *time)
{
	time64_t sec = ktime_get_real_seconds();


	if ((sec ^ time->tv_sec) & ~7)
		time->tv_sec = sec;
}
