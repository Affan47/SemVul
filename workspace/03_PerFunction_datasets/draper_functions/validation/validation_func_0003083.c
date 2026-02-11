rt_mutex_getprio(struct task_struct *task)
{
	if (likely(!task_has_pi_waiters(task)))
		return task->normal_prio;

	return min(task_top_pi_waiter(task)->prio,
		   task->normal_prio);
}
