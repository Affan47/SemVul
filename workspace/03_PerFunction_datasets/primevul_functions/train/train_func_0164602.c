static void __enqueue_entity(struct cfs_rq *cfs_rq, struct sched_entity *se)
{
	struct rb_node **link = &cfs_rq->tasks_timeline.rb_node;
	struct rb_node *parent = NULL;
	struct sched_entity *entry;
	s64 key = entity_key(cfs_rq, se);
	int leftmost = 1;


	while (*link) {
		parent = *link;
		entry = rb_entry(parent, struct sched_entity, run_node);


		if (key < entity_key(cfs_rq, entry)) {
			link = &parent->rb_left;
		} else {
			link = &parent->rb_right;
			leftmost = 0;
		}
	}


	if (leftmost) {
		cfs_rq->rb_leftmost = &se->run_node;


		cfs_rq->min_vruntime =
			max_vruntime(cfs_rq->min_vruntime, se->vruntime);
	}

	rb_link_node(&se->run_node, parent, link);
	rb_insert_color(&se->run_node, &cfs_rq->tasks_timeline);
}
