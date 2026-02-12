static void call_timer_fn(struct timer_list *timer, void (*fn)(unsigned long),
			  unsigned long data)
{
	int count = preempt_count();

#ifdef CONFIG_LOCKDEP


	struct lockdep_map lockdep_map;

	lockdep_copy_map(&lockdep_map, &timer->lockdep_map);
#endif


	lock_map_acquire(&lockdep_map);

	trace_timer_expire_entry(timer);
	fn(data);
	trace_timer_expire_exit(timer);

	lock_map_release(&lockdep_map);

	if (count != preempt_count()) {
		WARN_ONCE(1, "timer: %pF preempt leak: %08x -> %08x\n",
			  fn, count, preempt_count());


		preempt_count_set(count);
	}
}
