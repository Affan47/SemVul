void preempt_count_sub(int val)
{
#ifdef CONFIG_DEBUG_PREEMPT


	if (DEBUG_LOCKS_WARN_ON(val > preempt_count()))
		return;


	if (DEBUG_LOCKS_WARN_ON((val < PREEMPT_MASK) &&
			!(preempt_count() & PREEMPT_MASK)))
		return;
#endif

	if (preempt_count() == val)
		trace_preempt_on(CALLER_ADDR0, get_lock_parent_ip());
	__preempt_count_sub(val);
}
