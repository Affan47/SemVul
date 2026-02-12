static bool idling_boosts_thr_without_issues(struct bfq_data *bfqd,
					     struct bfq_queue *bfqq)
{
	bool rot_without_queueing =
		!blk_queue_nonrot(bfqd->queue) && !bfqd->hw_tag,
		bfqq_sequential_and_IO_bound,
		idling_boosts_thr;


	if (unlikely(!bfqq_process_refs(bfqq)))
		return false;

	bfqq_sequential_and_IO_bound = !BFQQ_SEEKY(bfqq) &&
		bfq_bfqq_IO_bound(bfqq) && bfq_bfqq_has_short_ttime(bfqq);


	idling_boosts_thr = rot_without_queueing ||
		((!blk_queue_nonrot(bfqd->queue) || !bfqd->hw_tag) &&
		 bfqq_sequential_and_IO_bound);


	return idling_boosts_thr &&
		bfqd->wr_busy_queues == 0;
}
