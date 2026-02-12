static void bfq_reset_inject_limit(struct bfq_data *bfqd,
				   struct bfq_queue *bfqq)
{

	bfqq->last_serv_time_ns = 0;


	bfqd->waited_rq = NULL;


	if (bfq_bfqq_has_short_ttime(bfqq))
		bfqq->inject_limit = 0;
	else
		bfqq->inject_limit = 1;

	bfqq->decrease_time_jif = jiffies;
}
