static void bfq_add_request(struct request *rq)
{
	struct bfq_queue *bfqq = RQ_BFQQ(rq);
	struct bfq_data *bfqd = bfqq->bfqd;
	struct request *next_rq, *prev;
	unsigned int old_wr_coeff = bfqq->wr_coeff;
	bool interactive = false;

	bfq_log_bfqq(bfqd, bfqq, "add_request %d", rq_is_sync(rq));
	bfqq->queued[rq_is_sync(rq)]++;
	bfqd->queued++;

	if (RB_EMPTY_ROOT(&bfqq->sort_list) && bfq_bfqq_sync(bfqq)) {


		if (bfqd->last_completed_rq_bfqq &&
		    !bfq_bfqq_has_short_ttime(bfqq) &&
		    ktime_get_ns() - bfqd->last_completion <
		    200 * NSEC_PER_USEC) {
			if (bfqd->last_completed_rq_bfqq != bfqq &&
			    bfqd->last_completed_rq_bfqq !=
			    bfqq->waker_bfqq) {


				bfqq->waker_bfqq = bfqd->last_completed_rq_bfqq;


				if (!hlist_unhashed(&bfqq->woken_list_node))
					hlist_del_init(&bfqq->woken_list_node);
				hlist_add_head(&bfqq->woken_list_node,
				    &bfqd->last_completed_rq_bfqq->woken_list);

				bfq_clear_bfqq_has_waker(bfqq);
			} else if (bfqd->last_completed_rq_bfqq ==
				   bfqq->waker_bfqq &&
				   !bfq_bfqq_has_waker(bfqq)) {


				bfq_mark_bfqq_has_waker(bfqq);
			}
		}


		if (time_is_before_eq_jiffies(bfqq->decrease_time_jif +
					     msecs_to_jiffies(1000)))
			bfq_reset_inject_limit(bfqd, bfqq);


		if (bfqq == bfqd->in_service_queue &&
		    (bfqd->rq_in_driver == 0 ||
		     (bfqq->last_serv_time_ns > 0 &&
		      bfqd->rqs_injected && bfqd->rq_in_driver > 0)) &&
		    time_is_before_eq_jiffies(bfqq->decrease_time_jif +
					      msecs_to_jiffies(10))) {
			bfqd->last_empty_occupied_ns = ktime_get_ns();


			bfqd->wait_dispatch = true;


			if (bfqd->rq_in_driver == 0)
				bfqd->rqs_injected = false;
		}
	}

	elv_rb_add(&bfqq->sort_list, rq);


	prev = bfqq->next_rq;
	next_rq = bfq_choose_req(bfqd, bfqq->next_rq, rq, bfqd->last_position);
	bfqq->next_rq = next_rq;


	if (unlikely(!bfqd->nonrot_with_queueing && prev != bfqq->next_rq))
		bfq_pos_tree_add_move(bfqd, bfqq);

	if (!bfq_bfqq_busy(bfqq))
		bfq_bfqq_handle_idle_busy_switch(bfqd, bfqq, old_wr_coeff,
						 rq, &interactive);
	else {
		if (bfqd->low_latency && old_wr_coeff == 1 && !rq_is_sync(rq) &&
		    time_is_before_jiffies(
				bfqq->last_wr_start_finish +
				bfqd->bfq_wr_min_inter_arr_async)) {
			bfqq->wr_coeff = bfqd->bfq_wr_coeff;
			bfqq->wr_cur_max_time = bfq_wr_duration(bfqd);

			bfqd->wr_busy_queues++;
			bfqq->entity.prio_changed = 1;
		}
		if (prev != bfqq->next_rq)
			bfq_updated_next_req(bfqd, bfqq);
	}


	if (bfqd->low_latency &&
		(old_wr_coeff == 1 || bfqq->wr_coeff == 1 || interactive))
		bfqq->last_wr_start_finish = jiffies;
}
