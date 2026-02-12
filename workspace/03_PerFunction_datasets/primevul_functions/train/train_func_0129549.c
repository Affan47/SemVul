static void wq_unbind_fn(struct work_struct *work)
{
	int cpu = smp_processor_id();
	struct worker_pool *pool;
	struct worker *worker;

	for_each_cpu_worker_pool(pool, cpu) {
		mutex_lock(&pool->attach_mutex);
		spin_lock_irq(&pool->lock);


		for_each_pool_worker(worker, pool)
			worker->flags |= WORKER_UNBOUND;

		pool->flags |= POOL_DISASSOCIATED;

		spin_unlock_irq(&pool->lock);
		mutex_unlock(&pool->attach_mutex);


		schedule();


		atomic_set(&pool->nr_running, 0);


		spin_lock_irq(&pool->lock);
		wake_up_worker(pool);
		spin_unlock_irq(&pool->lock);
	}
}
