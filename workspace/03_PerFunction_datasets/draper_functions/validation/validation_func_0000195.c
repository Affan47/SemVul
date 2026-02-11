sa_timer_get_secs(void)
{
	u_int sec;

#ifndef _POSIX_TIMERS
	struct timeval tv;

	gettimeofday(&tv, NULL);
	sec = tv.tv_sec;
#else
	struct timespec ts;
	int rc;

	rc = clock_gettime(CLOCK_MONOTONIC, &ts);
	ASSERT_NOTIMPL(rc == 0);
	sec = ts.tv_sec;
#endif
	return sec;
}
