static
void bfq_release_process_ref(struct bfq_data *bfqd, struct bfq_queue *bfqq)
{


	if (bfq_bfqq_busy(bfqq) && RB_EMPTY_ROOT(&bfqq->sort_list) &&
	    bfqq != bfqd->in_service_queue)
		bfq_del_bfqq_busy(bfqd, bfqq, false);

	bfq_put_queue(bfqq);
}
