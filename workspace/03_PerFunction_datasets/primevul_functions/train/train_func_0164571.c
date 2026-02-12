static void switched_to_fair(struct rq *rq, struct task_struct *p,
			     int running)
{


	if (running)
		resched_task(rq->curr);
	else
		check_preempt_curr(rq, p);
}
