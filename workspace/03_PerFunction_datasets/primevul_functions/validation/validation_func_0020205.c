*/
void bfq_weights_tree_add(struct bfq_data *bfqd, struct bfq_queue *bfqq,
			  struct rb_root_cached *root)
{
	struct bfq_entity *entity = &bfqq->entity;
	struct rb_node **new = &(root->rb_root.rb_node), *parent = NULL;
	bool leftmost = true;


	if (bfqq->weight_counter)
		return;

	while (*new) {
		struct bfq_weight_counter *__counter = container_of(*new,
						struct bfq_weight_counter,
						weights_node);
		parent = *new;

		if (entity->weight == __counter->weight) {
			bfqq->weight_counter = __counter;
			goto inc_counter;
		}
		if (entity->weight < __counter->weight)
			new = &((*new)->rb_left);
		else {
			new = &((*new)->rb_right);
			leftmost = false;
		}
	}

	bfqq->weight_counter = kzalloc(sizeof(struct bfq_weight_counter),
				       GFP_ATOMIC);


	if (unlikely(!bfqq->weight_counter))
		return;

	bfqq->weight_counter->weight = entity->weight;
	rb_link_node(&bfqq->weight_counter->weights_node, parent, new);
	rb_insert_color_cached(&bfqq->weight_counter->weights_node, root,
				leftmost);

inc_counter:
	bfqq->weight_counter->num_active++;
	bfqq->ref++;
}
