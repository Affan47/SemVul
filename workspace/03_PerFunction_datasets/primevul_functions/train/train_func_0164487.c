void hrtimer_run_queues(void)
{
	struct hrtimer_cpu_base *cpu_base = &__get_cpu_var(hrtimer_bases);
	int i;

	if (hrtimer_hres_active())
		return;


	if (tick_check_oneshot_change(!hrtimer_is_hres_enabled()))
		if (hrtimer_switch_to_hres())
			return;

	hrtimer_get_softirq_time(cpu_base);

	for (i = 0; i < HRTIMER_MAX_CLOCK_BASES; i++)
		run_hrtimer_queue(cpu_base, i);
}
