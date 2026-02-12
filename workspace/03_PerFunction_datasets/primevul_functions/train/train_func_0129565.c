static bool manage_workers(struct worker *worker)
{
	struct worker_pool *pool = worker->pool;


	if (!mutex_trylock(&pool->manager_arb))
		return false;
	pool->manager = worker;

	maybe_create_worker(pool);

	pool->manager = NULL;
	mutex_unlock(&pool->manager_arb);
	return true;
}
