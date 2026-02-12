u64 get_next_timer_interrupt(unsigned long basej, u64 basem)
{
	struct timer_base *base = this_cpu_ptr(&timer_bases[BASE_STD]);
	u64 expires = KTIME_MAX;
	unsigned long nextevt;
	bool is_max_delta;


	if (cpu_is_offline(smp_processor_id()))
		return expires;

	spin_lock(&base->lock);
	nextevt = __next_timer_interrupt(base);
	is_max_delta = (nextevt == base->clk + NEXT_TIMER_MAX_DELTA);
	base->next_expiry = nextevt;


	if (time_after(basej, base->clk)) {
		if (time_after(nextevt, basej))
			base->clk = basej;
		else if (time_after(nextevt, base->clk))
			base->clk = nextevt;
	}

	if (time_before_eq(nextevt, basej)) {
		expires = basem;
		base->is_idle = false;
	} else {
		if (!is_max_delta)
			expires = basem + (nextevt - basej) * TICK_NSEC;


		if ((expires - basem) > TICK_NSEC)
			base->is_idle = true;
	}
	spin_unlock(&base->lock);

	return cmp_next_hrtimer_event(basem, expires);
}
