update_stats_dequeue(struct cfs_rq *cfs_rq, struct sched_entity *se)
{


	if (se != cfs_rq->curr)
		update_stats_wait_end(cfs_rq, se);
}
