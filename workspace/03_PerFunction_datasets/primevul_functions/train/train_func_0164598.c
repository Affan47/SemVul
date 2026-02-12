static void prio_changed_fair(struct rq *rq, struct task_struct *p,
			      int oldprio, int running)
{


	if (running) {
		if (p->prio > oldprio)
			resched_task(rq->curr);
	} else
		check_preempt_curr(rq, p);
}
