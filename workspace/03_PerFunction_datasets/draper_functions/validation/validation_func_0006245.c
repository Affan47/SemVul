compare_weight(struct call_queue *rq, struct member *member)
{
	struct call_queue *q;
	struct member *mem;
	int found = 0;
	struct ao2_iterator queue_iter;

	queue_iter = ao2_iterator_init(queues, 0);
	while ((q = ao2_t_iterator_next(&queue_iter, "Iterate through queues"))) {
		if (q == rq) {
			queue_t_unref(q, "Done with iterator");
			continue;
		}
		ao2_lock(q);
		if (q->count && q->members) {
			if ((mem = ao2_find(q->members, member, OBJ_POINTER))) {
				ast_debug(1, "Found matching member %s in queue '%s'\n", mem->interface, q->name);
				if (q->weight > rq->weight && q->count >= num_available_members(q)) {
					ast_debug(1, "Queue '%s' (weight %d, calls %d) is preferred over '%s' (weight %d, calls %d)\n", q->name, q->weight, q->count, rq->name, rq->weight, rq->count);
					found = 1;
				}
				ao2_ref(mem, -1);
			}
		}
		ao2_unlock(q);
		queue_t_unref(q, "Done with iterator");
		if (found) {
			break;
		}
	}
	ao2_iterator_destroy(&queue_iter);
	return found;
}
