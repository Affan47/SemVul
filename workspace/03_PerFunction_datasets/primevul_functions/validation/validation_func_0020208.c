*/
static struct bfq_queue *bfq_select_queue(struct bfq_data *bfqd)
{
	struct bfq_queue *bfqq;
	struct request *next_rq;
	enum bfqq_expiration reason = BFQQE_BUDGET_TIMEOUT;

	bfqq = bfqd->in_service_queue;
	if (!bfqq)
		goto new_queue;

	bfq_log_bfqq(bfqd, bfqq, "select_queue: already in-service queue");


	if (bfq_may_expire_for_budg_timeout(bfqq) &&
	    !bfq_bfqq_must_idle(bfqq))
		goto expire;

check_queue:


	next_rq = bfqq->next_rq;


	if (next_rq) {
		if (bfq_serv_to_charge(next_rq, bfqq) >
			bfq_bfqq_budget_left(bfqq)) {


			reason = BFQQE_BUDGET_EXHAUSTED;
			goto expire;
		} else {


			if (bfq_bfqq_wait_request(bfqq)) {


				bfq_clear_bfqq_wait_request(bfqq);
				hrtimer_try_to_cancel(&bfqd->idle_slice_timer);
			}
			goto keep_queue;
		}
	}


	if (bfq_bfqq_wait_request(bfqq) ||
	    (bfqq->dispatched != 0 && bfq_better_to_idle(bfqq))) {
		struct bfq_queue *async_bfqq =
			bfqq->bic && bfqq->bic->bfqq[0] &&
			bfq_bfqq_busy(bfqq->bic->bfqq[0]) &&
			bfqq->bic->bfqq[0]->next_rq ?
			bfqq->bic->bfqq[0] : NULL;


		if (async_bfqq &&
		    icq_to_bic(async_bfqq->next_rq->elv.icq) == bfqq->bic &&
		    bfq_serv_to_charge(async_bfqq->next_rq, async_bfqq) <=
		    bfq_bfqq_budget_left(async_bfqq))
			bfqq = bfqq->bic->bfqq[0];
		else if (bfq_bfqq_has_waker(bfqq) &&
			   bfq_bfqq_busy(bfqq->waker_bfqq) &&
			   bfqq->next_rq &&
			   bfq_serv_to_charge(bfqq->waker_bfqq->next_rq,
					      bfqq->waker_bfqq) <=
			   bfq_bfqq_budget_left(bfqq->waker_bfqq)
			)
			bfqq = bfqq->waker_bfqq;
		else if (!idling_boosts_thr_without_issues(bfqd, bfqq) &&
			 (bfqq->wr_coeff == 1 || bfqd->wr_busy_queues > 1 ||
			  !bfq_bfqq_has_short_ttime(bfqq)))
			bfqq = bfq_choose_bfqq_for_injection(bfqd);
		else
			bfqq = NULL;

		goto keep_queue;
	}

	reason = BFQQE_NO_MORE_REQUESTS;
expire:
	bfq_bfqq_expire(bfqd, bfqq, false, reason);
new_queue:
	bfqq = bfq_set_in_service_queue(bfqd);
	if (bfqq) {
		bfq_log_bfqq(bfqd, bfqq, "select_queue: checking new queue");
		goto check_queue;
	}
keep_queue:
	if (bfqq)
		bfq_log_bfqq(bfqd, bfqq, "select_queue: returned this queue");
	else
		bfq_log(bfqd, "select_queue: no queue returned");

	return bfqq;
}
