static void rebind_workers(struct worker_pool *pool)
{
	struct worker *worker;

	lockdep_assert_held(&pool->attach_mutex);


	for_each_pool_worker(worker, pool)
		WARN_ON_ONCE(set_cpus_allowed_ptr(worker->task,
						  pool->attrs->cpumask) < 0);

	spin_lock_irq(&pool->lock);


	if (!(pool->flags & POOL_DISASSOCIATED)) {
		spin_unlock_irq(&pool->lock);
		return;
	}

	pool->flags &= ~POOL_DISASSOCIATED;

	for_each_pool_worker(worker, pool) {
		unsigned int worker_flags = worker->flags;


		if (worker_flags & WORKER_IDLE)
			wake_up_process(worker->task);


		WARN_ON_ONCE(!(worker_flags & WORKER_UNBOUND));
		worker_flags |= WORKER_REBOUND;
		worker_flags &= ~WORKER_UNBOUND;
		ACCESS_ONCE(worker->flags) = worker_flags;
	}

	spin_unlock_irq(&pool->lock);
}
