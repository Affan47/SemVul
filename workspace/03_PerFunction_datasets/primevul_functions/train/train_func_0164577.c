static void put_prev_entity(struct cfs_rq *cfs_rq, struct sched_entity *prev)
{


	if (prev->on_rq)
		update_curr(cfs_rq);

	check_spread(cfs_rq, prev);
	if (prev->on_rq) {
		update_stats_wait_start(cfs_rq, prev);

		__enqueue_entity(cfs_rq, prev);
	}
	cfs_rq->curr = NULL;
}
