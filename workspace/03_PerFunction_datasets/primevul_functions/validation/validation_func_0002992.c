virtio_start_timer(struct acrn_timer *timer, time_t sec, time_t nsec)
{
	struct itimerspec ts;


	ts.it_interval.tv_sec = 0;
	ts.it_interval.tv_nsec = 0;

	ts.it_value.tv_sec = sec;
	ts.it_value.tv_nsec = nsec;
	if (acrn_timer_settime(timer, &ts) != 0) {
		pr_err("acrn timer set time failed\n");
		return;
	}
}
