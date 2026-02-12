void clock_was_set(void)
{
#ifdef CONFIG_HIGH_RES_TIMERS

	on_each_cpu(retrigger_next_event, NULL, 1);
#endif
	timerfd_clock_was_set();
}
