stage_work(struct work *work)
{
	applog(LOG_DEBUG, "Pushing work from pool %d to hash queue", work->pool->pool_no);
	work->work_block = work_block;
	test_work_current(work);
	work->pool->works++;
	hash_push(work);
}
