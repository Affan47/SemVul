__task_queue(struct task *task)
{
	if (likely(task_in_wq(task)))
		__task_unlink_wq(task);


	task->wq.key = task->expire;
#ifdef DEBUG_CHECK_INVALID_EXPIRATION_DATES
	if (tick_is_lt(task->wq.key, now_ms))

		return;
#endif

	if (likely(last_timer &&
		   last_timer->node.bit < 0 &&
		   last_timer->key == task->wq.key &&
		   last_timer->node.node_p)) {


		eb_insert_dup(&last_timer->node, &task->wq.node);
		if (task->wq.node.bit < last_timer->node.bit)
			last_timer = &task->wq;
		return;
	}
	eb32_insert(&timers, &task->wq);


	if (task->wq.node.node_p && (!last_timer || (task->wq.node.bit < last_timer->node.bit)))
		last_timer = &task->wq;
	return;
}
