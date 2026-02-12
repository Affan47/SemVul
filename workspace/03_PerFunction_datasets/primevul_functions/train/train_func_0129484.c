static void link_pwq(struct pool_workqueue *pwq)
{
	struct workqueue_struct *wq = pwq->wq;

	lockdep_assert_held(&wq->mutex);


	if (!list_empty(&pwq->pwqs_node))
		return;


	pwq->work_color = wq->work_color;


	pwq_adjust_max_active(pwq);


	list_add_rcu(&pwq->pwqs_node, &wq->pwqs);
}
