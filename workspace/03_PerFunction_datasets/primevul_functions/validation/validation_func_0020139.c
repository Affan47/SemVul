static void bfq_update_has_short_ttime(struct bfq_data *bfqd,
				       struct bfq_queue *bfqq,
				       struct bfq_io_cq *bic)
{
	bool has_short_ttime = true, state_changed;


	if (!bfq_bfqq_sync(bfqq) || bfq_class_idle(bfqq) ||
	    bfqd->bfq_slice_idle == 0)
		return;


	if (time_is_after_eq_jiffies(bfqq->split_time +
				     bfqd->bfq_wr_min_idle_time))
		return;


	if (atomic_read(&bic->icq.ioc->active_ref) == 0 ||
	    (bfq_sample_valid(bfqq->ttime.ttime_samples) &&
	     bfqq->ttime.ttime_mean > bfqd->bfq_slice_idle))
		has_short_ttime = false;

	state_changed = has_short_ttime != bfq_bfqq_has_short_ttime(bfqq);

	if (has_short_ttime)
		bfq_mark_bfqq_has_short_ttime(bfqq);
	else
		bfq_clear_bfqq_has_short_ttime(bfqq);


	if (state_changed && bfqq->last_serv_time_ns == 0 &&
	    (time_is_before_eq_jiffies(bfqq->decrease_time_jif +
				      msecs_to_jiffies(100)) ||
	     !has_short_ttime))
		bfq_reset_inject_limit(bfqd, bfqq);
}
