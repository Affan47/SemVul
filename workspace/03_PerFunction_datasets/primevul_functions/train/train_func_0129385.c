static void pwq_adjust_max_active(struct pool_workqueue *pwq)
{
	struct workqueue_struct *wq = pwq->wq;
	bool freezable = wq->flags & WQ_FREEZABLE;
	unsigned long flags;


	lockdep_assert_held(&wq->mutex);


	if (!freezable && pwq->max_active == wq->saved_max_active)
		return;


	spin_lock_irqsave(&pwq->pool->lock, flags);


	if (!freezable || !workqueue_freezing) {
		pwq->max_active = wq->saved_max_active;

		while (!list_empty(&pwq->delayed_works) &&
		       pwq->nr_active < pwq->max_active)
			pwq_activate_first_delayed(pwq);


		wake_up_worker(pwq->pool);
	} else {
		pwq->max_active = 0;
	}

	spin_unlock_irqrestore(&pwq->pool->lock, flags);
}
