*/
void bfq_bfqq_expire(struct bfq_data *bfqd,
		     struct bfq_queue *bfqq,
		     bool compensate,
		     enum bfqq_expiration reason)
{
	bool slow;
	unsigned long delta = 0;
	struct bfq_entity *entity = &bfqq->entity;


	slow = bfq_bfqq_is_slow(bfqd, bfqq, compensate, reason, &delta);


	if (bfqq->wr_coeff == 1 &&
	    (slow ||
	     (reason == BFQQE_BUDGET_TIMEOUT &&
	      bfq_bfqq_budget_left(bfqq) >=  entity->budget / 3)))
		bfq_bfqq_charge_time(bfqd, bfqq, delta);

	if (reason == BFQQE_TOO_IDLE &&
	    entity->service <= 2 * entity->budget / 10)
		bfq_clear_bfqq_IO_bound(bfqq);

	if (bfqd->low_latency && bfqq->wr_coeff == 1)
		bfqq->last_wr_start_finish = jiffies;

	if (bfqd->low_latency && bfqd->bfq_wr_max_softrt_rate > 0 &&
	    RB_EMPTY_ROOT(&bfqq->sort_list)) {


		if (bfqq->dispatched == 0 &&
		    bfqq->wr_coeff != bfqd->bfq_wr_coeff)
			bfqq->soft_rt_next_start =
				bfq_bfqq_softrt_next_start(bfqd, bfqq);
		else if (bfqq->dispatched > 0) {


			bfq_mark_bfqq_softrt_update(bfqq);
		}
	}

	bfq_log_bfqq(bfqd, bfqq,
		"expire (%d, slow %d, num_disp %d, short_ttime %d)", reason,
		slow, bfqq->dispatched, bfq_bfqq_has_short_ttime(bfqq));


	bfqd->rqs_injected = bfqd->wait_dispatch = false;
	bfqd->waited_rq = NULL;


	__bfq_bfqq_recalc_budget(bfqd, bfqq, reason);
	if (__bfq_bfqq_expire(bfqd, bfqq, reason))

		return;


	if (!bfq_bfqq_busy(bfqq) &&
	    reason != BFQQE_BUDGET_TIMEOUT &&
	    reason != BFQQE_BUDGET_EXHAUSTED) {
		bfq_mark_bfqq_non_blocking_wait_rq(bfqq);


	} else
		entity->service = 0;


	entity = entity->parent;
	for_each_entity(entity)
		entity->service = 0;
}
