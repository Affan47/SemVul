
static void bfq_bfqq_end_wr(struct bfq_queue *bfqq)
{
	if (bfq_bfqq_busy(bfqq))
		bfqq->bfqd->wr_busy_queues--;
	bfqq->wr_coeff = 1;
	bfqq->wr_cur_max_time = 0;
	bfqq->last_wr_start_finish = jiffies;


	bfqq->entity.prio_changed = 1;
}
