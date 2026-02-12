int del_timer_sync(struct timer_list *timer)
{
	int ret;

#ifdef CONFIG_LOCKDEP
	unsigned long flags;


	local_irq_save(flags);
	lock_map_acquire(&timer->lockdep_map);
	lock_map_release(&timer->lockdep_map);
	local_irq_restore(flags);
#endif


	WARN_ON(in_irq() && !(timer->flags & TIMER_IRQSAFE));

	do {
		ret = try_to_del_timer_sync(timer);

		if (unlikely(ret < 0)) {
			del_timer_wait_running(timer);
			cpu_relax();
		}
	} while (ret < 0);

	return ret;
}
