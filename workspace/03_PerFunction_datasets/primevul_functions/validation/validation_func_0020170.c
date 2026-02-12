*/
static bool bfq_better_to_idle(struct bfq_queue *bfqq)
{
	struct bfq_data *bfqd = bfqq->bfqd;
	bool idling_boosts_thr_with_no_issue, idling_needed_for_service_guar;


	if (unlikely(!bfqq_process_refs(bfqq)))
		return false;

	if (unlikely(bfqd->strict_guarantees))
		return true;


	if (bfqd->bfq_slice_idle == 0 || !bfq_bfqq_sync(bfqq) ||
	   bfq_class_idle(bfqq))
		return false;

	idling_boosts_thr_with_no_issue =
		idling_boosts_thr_without_issues(bfqd, bfqq);

	idling_needed_for_service_guar =
		idling_needed_for_service_guarantees(bfqd, bfqq);


	return idling_boosts_thr_with_no_issue ||
		idling_needed_for_service_guar;
}
