static struct bfq_queue *
bfq_choose_bfqq_for_injection(struct bfq_data *bfqd)
{
	struct bfq_queue *bfqq, *in_serv_bfqq = bfqd->in_service_queue;
	unsigned int limit = in_serv_bfqq->inject_limit;


	bool in_serv_always_inject = in_serv_bfqq->wr_coeff == 1 ||
		!bfq_bfqq_has_short_ttime(in_serv_bfqq);


	if (limit == 0 && in_serv_bfqq->last_serv_time_ns == 0 &&
	    bfq_bfqq_wait_request(in_serv_bfqq) &&
	    time_is_before_eq_jiffies(bfqd->last_idling_start_jiffies +
				      bfqd->bfq_slice_idle)
		)
		limit = 1;

	if (bfqd->rq_in_driver >= limit)
		return NULL;


	list_for_each_entry(bfqq, &bfqd->active_list, bfqq_list)
		if (!RB_EMPTY_ROOT(&bfqq->sort_list) &&
		    (in_serv_always_inject || bfqq->wr_coeff > 1) &&
		    bfq_serv_to_charge(bfqq->next_rq, bfqq) <=
		    bfq_bfqq_budget_left(bfqq)) {


			if (blk_queue_nonrot(bfqd->queue) &&
			    blk_rq_sectors(bfqq->next_rq) >=
			    BFQQ_SECT_THR_NONROT)
				limit = min_t(unsigned int, 1, limit);
			else
				limit = in_serv_bfqq->inject_limit;

			if (bfqd->rq_in_driver < limit) {
				bfqd->rqs_injected = true;
				return bfqq;
			}
		}

	return NULL;
}
