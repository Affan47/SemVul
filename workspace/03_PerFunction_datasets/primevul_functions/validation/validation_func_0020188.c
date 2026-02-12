*/
static void bfq_update_inject_limit(struct bfq_data *bfqd,
				    struct bfq_queue *bfqq)
{
	u64 tot_time_ns = ktime_get_ns() - bfqd->last_empty_occupied_ns;
	unsigned int old_limit = bfqq->inject_limit;

	if (bfqq->last_serv_time_ns > 0 && bfqd->rqs_injected) {
		u64 threshold = (bfqq->last_serv_time_ns * 3)>>1;

		if (tot_time_ns >= threshold && old_limit > 0) {
			bfqq->inject_limit--;
			bfqq->decrease_time_jif = jiffies;
		} else if (tot_time_ns < threshold &&
			   old_limit <= bfqd->max_rq_in_driver)
			bfqq->inject_limit++;
	}


	if ((bfqq->last_serv_time_ns == 0 && bfqd->rq_in_driver == 1) ||
	    tot_time_ns < bfqq->last_serv_time_ns) {
		if (bfqq->last_serv_time_ns == 0) {


			bfqq->inject_limit = max_t(unsigned int, 1, old_limit);
		}
		bfqq->last_serv_time_ns = tot_time_ns;
	} else if (!bfqd->rqs_injected && bfqd->rq_in_driver == 1)


		bfqq->last_serv_time_ns = tot_time_ns;


	bfqd->waited_rq = NULL;
	bfqd->rqs_injected = false;
}
