void destroy_workqueue(struct workqueue_struct *wq)
{
	struct pool_workqueue *pwq;
	int node;


	drain_workqueue(wq);


	mutex_lock(&wq->mutex);
	for_each_pwq(pwq, wq) {
		int i;

		for (i = 0; i < WORK_NR_COLORS; i++) {
			if (WARN_ON(pwq->nr_in_flight[i])) {
				mutex_unlock(&wq->mutex);
				show_workqueue_state();
				return;
			}
		}

		if (WARN_ON((pwq != wq->dfl_pwq) && (pwq->refcnt > 1)) ||
		    WARN_ON(pwq->nr_active) ||
		    WARN_ON(!list_empty(&pwq->delayed_works))) {
			mutex_unlock(&wq->mutex);
			show_workqueue_state();
			return;
		}
	}
	mutex_unlock(&wq->mutex);


	mutex_lock(&wq_pool_mutex);
	list_del_rcu(&wq->list);
	mutex_unlock(&wq_pool_mutex);

	workqueue_sysfs_unregister(wq);

	if (wq->rescuer)
		kthread_stop(wq->rescuer->task);

	if (!(wq->flags & WQ_UNBOUND)) {


		call_rcu_sched(&wq->rcu, rcu_free_wq);
	} else {


		for_each_node(node) {
			pwq = rcu_access_pointer(wq->numa_pwq_tbl[node]);
			RCU_INIT_POINTER(wq->numa_pwq_tbl[node], NULL);
			put_pwq_unlocked(pwq);
		}


		pwq = wq->dfl_pwq;
		wq->dfl_pwq = NULL;
		put_pwq_unlocked(pwq);
	}
}
