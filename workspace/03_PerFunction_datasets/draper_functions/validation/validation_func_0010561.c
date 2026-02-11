workqueue_cpu_up_callback(struct notifier_block *nfb,
					       unsigned long action,
					       void *hcpu)
{
	int cpu = (unsigned long)hcpu;
	struct worker_pool *pool;
	struct workqueue_struct *wq;
	int pi;

	switch (action & ~CPU_TASKS_FROZEN) {
	case CPU_UP_PREPARE:
		for_each_cpu_worker_pool(pool, cpu) {
			if (pool->nr_workers)
				continue;
			if (!create_worker(pool))
				return NOTIFY_BAD;
		}
		break;

	case CPU_DOWN_FAILED:
	case CPU_ONLINE:
		mutex_lock(&wq_pool_mutex);

		for_each_pool(pool, pi) {
			mutex_lock(&pool->attach_mutex);

			if (pool->cpu == cpu)
				rebind_workers(pool);
			else if (pool->cpu < 0)
				restore_unbound_workers_cpumask(pool, cpu);

			mutex_unlock(&pool->attach_mutex);
		}


		list_for_each_entry(wq, &workqueues, list)
			wq_update_unbound_numa(wq, cpu, true);

		mutex_unlock(&wq_pool_mutex);
		break;
	}
	return NOTIFY_OK;
}
