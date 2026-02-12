*/
static bool bfq_bfqq_update_budg_for_activation(struct bfq_data *bfqd,
						struct bfq_queue *bfqq,
						bool arrived_in_time)
{
	struct bfq_entity *entity = &bfqq->entity;


	if (bfq_bfqq_non_blocking_wait_rq(bfqq) && arrived_in_time &&
	    bfq_bfqq_budget_left(bfqq) > 0) {


		entity->budget = min_t(unsigned long,
				       bfq_bfqq_budget_left(bfqq),
				       bfqq->max_budget);


		entity->service = 0;

		return true;
	}


	entity->service = 0;
	entity->budget = max_t(unsigned long, bfqq->max_budget,
			       bfq_serv_to_charge(bfqq->next_rq, bfqq));
	bfq_clear_bfqq_non_blocking_wait_rq(bfqq);
	return false;
}
