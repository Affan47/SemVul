*/
void bfq_weights_tree_remove(struct bfq_data *bfqd,
			     struct bfq_queue *bfqq)
{
	struct bfq_entity *entity = bfqq->entity.parent;

	for_each_entity(entity) {
		struct bfq_sched_data *sd = entity->my_sched_data;

		if (sd->next_in_service || sd->in_service_entity) {


			break;
		}


		if (entity->in_groups_with_pending_reqs) {
			entity->in_groups_with_pending_reqs = false;
			bfqd->num_groups_with_pending_reqs--;
		}
	}


	__bfq_weights_tree_remove(bfqd, bfqq,
				  &bfqd->queue_weights_tree);
}
