*/
static void bfq_finish_requeue_request(struct request *rq)
{
	struct bfq_queue *bfqq = RQ_BFQQ(rq);
	struct bfq_data *bfqd;


	if (unlikely(!(rq->rq_flags & RQF_ELVPRIV)))
		return;


	if (!rq->elv.icq || !bfqq)
		return;

	bfqd = bfqq->bfqd;

	if (rq->rq_flags & RQF_STARTED)
		bfqg_stats_update_completion(bfqq_group(bfqq),
					     rq->start_time_ns,
					     rq->io_start_time_ns,
					     rq->cmd_flags);

	if (likely(rq->rq_flags & RQF_STARTED)) {
		unsigned long flags;

		spin_lock_irqsave(&bfqd->lock, flags);

		if (rq == bfqd->waited_rq)
			bfq_update_inject_limit(bfqd, bfqq);

		bfq_completed_request(bfqq, bfqd);
		bfq_finish_requeue_request_body(bfqq);

		spin_unlock_irqrestore(&bfqd->lock, flags);
	} else {


		if (!RB_EMPTY_NODE(&rq->rb_node)) {
			bfq_remove_request(rq->q, rq);
			bfqg_stats_update_io_remove(bfqq_group(bfqq),
						    rq->cmd_flags);
		}
		bfq_finish_requeue_request_body(bfqq);
	}


	rq->elv.priv[0] = NULL;
	rq->elv.priv[1] = NULL;
}
