hrtimer_start(struct hrtimer *timer, ktime_t tim, const enum hrtimer_mode mode)
{
	struct hrtimer_clock_base *base, *new_base;
	unsigned long flags;
	int ret;

	base = lock_hrtimer_base(timer, &flags);


	ret = remove_hrtimer(timer, base);


	new_base = switch_hrtimer_base(timer, base);

	if (mode == HRTIMER_MODE_REL) {
		tim = ktime_add(tim, new_base->get_time());


#ifdef CONFIG_TIME_LOW_RES
		tim = ktime_add(tim, base->resolution);
#endif
	}
	timer->expires = tim;

	timer_stats_hrtimer_set_start_info(timer);

	enqueue_hrtimer(timer, new_base, base == new_base);

	unlock_hrtimer_base(timer, &flags);

	return ret;
}
