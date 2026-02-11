watchdog_disable(unsigned int cpu)
{
	struct hrtimer *hrtimer = raw_cpu_ptr(&watchdog_hrtimer);

	watchdog_set_prio(SCHED_NORMAL, 0);
	hrtimer_cancel(hrtimer);

	watchdog_nmi_disable(cpu);
}
