struct task_struct *wq_worker_sleeping(struct task_struct *task)
{
	struct worker *worker = kthread_data(task), *to_wakeup = NULL;
	struct worker_pool *pool;


	if (worker->flags & WORKER_NOT_RUNNING)
		return NULL;

	pool = worker->pool;


	if (WARN_ON_ONCE(pool->cpu != raw_smp_processor_id()))
		return NULL;


	if (atomic_dec_and_test(&pool->nr_running) &&
	    !list_empty(&pool->worklist))
		to_wakeup = first_idle_worker(pool);
	return to_wakeup ? to_wakeup->task : NULL;
}
