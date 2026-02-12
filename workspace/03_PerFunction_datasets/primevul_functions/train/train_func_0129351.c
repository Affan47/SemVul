static void migrate_hrtimer_list(struct hrtimer_clock_base *old_base,
				struct hrtimer_clock_base *new_base)
{
	struct hrtimer *timer;
	struct timerqueue_node *node;

	while ((node = timerqueue_getnext(&old_base->active))) {
		timer = container_of(node, struct hrtimer, node);
		BUG_ON(hrtimer_callback_running(timer));
		debug_deactivate(timer);


		__remove_hrtimer(timer, old_base, HRTIMER_STATE_ENQUEUED, 0);
		timer->base = new_base;


		enqueue_hrtimer(timer, new_base);
	}
}
