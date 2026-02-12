static void update_stats_enqueue(struct cfs_rq *cfs_rq, struct sched_entity *se)
{


	if (se != cfs_rq->curr)
		update_stats_wait_start(cfs_rq, se);
}
