static void worker_attach_to_pool(struct worker *worker,
				   struct worker_pool *pool)
{
	mutex_lock(&pool->attach_mutex);


	set_cpus_allowed_ptr(worker->task, pool->attrs->cpumask);


	if (pool->flags & POOL_DISASSOCIATED)
		worker->flags |= WORKER_UNBOUND;

	list_add_tail(&worker->node, &pool->workers);

	mutex_unlock(&pool->attach_mutex);
}
