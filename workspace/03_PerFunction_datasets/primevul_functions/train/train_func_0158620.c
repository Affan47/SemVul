void set_sched_clock_stable(void)
{
	__sched_clock_stable_early = 1;

	smp_mb();

	if (!sched_clock_running)
		return;

	__set_sched_clock_stable();
}
