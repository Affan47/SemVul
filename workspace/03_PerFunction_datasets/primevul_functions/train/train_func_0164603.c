static void yield_task_fair(struct rq *rq)
{
	struct task_struct *curr = rq->curr;
	struct cfs_rq *cfs_rq = task_cfs_rq(curr);
	struct sched_entity *rightmost, *se = &curr->se;


	if (unlikely(cfs_rq->nr_running == 1))
		return;

	if (likely(!sysctl_sched_compat_yield) && curr->policy != SCHED_BATCH) {
		__update_rq_clock(rq);


		update_curr(cfs_rq);

		return;
	}


	rightmost = __pick_last_entity(cfs_rq);


	if (unlikely(rightmost->vruntime < se->vruntime))
		return;


	se->vruntime = rightmost->vruntime + 1;
}
