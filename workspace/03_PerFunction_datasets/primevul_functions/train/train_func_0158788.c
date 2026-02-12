void blk_set_queue_dying(struct request_queue *q)
{
	blk_queue_flag_set(QUEUE_FLAG_DYING, q);


	blk_freeze_queue_start(q);

	if (queue_is_mq(q))
		blk_mq_wake_waiters(q);


	wake_up_all(&q->mq_freeze_wq);
}
