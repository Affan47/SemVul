entity_tick(struct cfs_rq *cfs_rq, struct sched_entity *curr, int queued)
{


	update_curr(cfs_rq);

#ifdef CONFIG_SCHED_HRTICK


	if (queued)
		return resched_task(rq_of(cfs_rq)->curr);


	if (!sched_feat(DOUBLE_TICK) &&
			hrtimer_active(&rq_of(cfs_rq)->hrtick_timer))
		return;
#endif

	if (cfs_rq->nr_running > 1 || !sched_feat(WAKEUP_PREEMPT))
		check_preempt_tick(cfs_rq, curr);
}
