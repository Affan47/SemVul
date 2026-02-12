asmlinkage __visible void __sched notrace preempt_schedule_notrace(void)
{
	enum ctx_state prev_ctx;

	if (likely(!preemptible()))
		return;

	do {
		preempt_disable_notrace();


		prev_ctx = exception_enter();
		__schedule(true);
		exception_exit(prev_ctx);

		preempt_enable_no_resched_notrace();
	} while (need_resched());
}
