static void hrtimer_reprogram(struct hrtimer *timer,
			      struct hrtimer_clock_base *base)
{
	struct hrtimer_cpu_base *cpu_base = this_cpu_ptr(&hrtimer_bases);
	ktime_t expires = ktime_sub(hrtimer_get_expires(timer), base->offset);

	WARN_ON_ONCE(hrtimer_get_expires_tv64(timer) < 0);


	if (base->cpu_base != cpu_base)
		return;


	if (cpu_base->in_hrtirq)
		return;


	if (expires < 0)
		expires = 0;

	if (expires >= cpu_base->expires_next)
		return;


	cpu_base->next_timer = timer;


	if (cpu_base->hang_detected)
		return;


	cpu_base->expires_next = expires;
	tick_program_event(expires, 1);
}
