int elevator_init_mq(struct request_queue *q)
{
	struct elevator_type *e;
	int err = 0;

	if (q->nr_hw_queues != 1)
		return 0;


	mutex_lock(&q->sysfs_lock);
	if (unlikely(q->elevator))
		goto out_unlock;

	e = elevator_get(q, "mq-deadline", false);
	if (!e)
		goto out_unlock;

	err = blk_mq_init_sched(q, e);
	if (err)
		elevator_put(e);
out_unlock:
	mutex_unlock(&q->sysfs_lock);
	return err;
}
