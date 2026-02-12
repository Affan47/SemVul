static int rescuer_thread(void *__rescuer)
{
	struct worker *rescuer = __rescuer;
	struct workqueue_struct *wq = rescuer->rescue_wq;
	struct list_head *scheduled = &rescuer->scheduled;
	bool should_stop;

	set_user_nice(current, RESCUER_NICE_LEVEL);


	rescuer->task->flags |= PF_WQ_WORKER;
repeat:
	set_current_state(TASK_INTERRUPTIBLE);


	should_stop = kthread_should_stop();


	spin_lock_irq(&wq_mayday_lock);

	while (!list_empty(&wq->maydays)) {
		struct pool_workqueue *pwq = list_first_entry(&wq->maydays,
					struct pool_workqueue, mayday_node);
		struct worker_pool *pool = pwq->pool;
		struct work_struct *work, *n;
		bool first = true;

		__set_current_state(TASK_RUNNING);
		list_del_init(&pwq->mayday_node);

		spin_unlock_irq(&wq_mayday_lock);

		worker_attach_to_pool(rescuer, pool);

		spin_lock_irq(&pool->lock);
		rescuer->pool = pool;


		WARN_ON_ONCE(!list_empty(scheduled));
		list_for_each_entry_safe(work, n, &pool->worklist, entry) {
			if (get_work_pwq(work) == pwq) {
				if (first)
					pool->watchdog_ts = jiffies;
				move_linked_works(work, scheduled, &n);
			}
			first = false;
		}

		if (!list_empty(scheduled)) {
			process_scheduled_works(rescuer);


			if (need_to_create_worker(pool)) {
				spin_lock(&wq_mayday_lock);
				get_pwq(pwq);
				list_move_tail(&pwq->mayday_node, &wq->maydays);
				spin_unlock(&wq_mayday_lock);
			}
		}


		put_pwq(pwq);


		if (need_more_worker(pool))
			wake_up_worker(pool);

		rescuer->pool = NULL;
		spin_unlock_irq(&pool->lock);

		worker_detach_from_pool(rescuer, pool);

		spin_lock_irq(&wq_mayday_lock);
	}

	spin_unlock_irq(&wq_mayday_lock);

	if (should_stop) {
		__set_current_state(TASK_RUNNING);
		rescuer->task->flags &= ~PF_WQ_WORKER;
		return 0;
	}


	WARN_ON_ONCE(!(rescuer->flags & WORKER_NOT_RUNNING));
	schedule();
	goto repeat;
}
