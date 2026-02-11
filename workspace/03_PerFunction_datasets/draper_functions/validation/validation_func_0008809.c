queue_map_remove_on_error(queue_t q,
			       int (*f) (queue_element_t, void *),
			       void (*g) (queue_element_t, void *), void *vp)
{
	queue_node_ptr_t p, last, temp;
	int ret;

	if (!q)
		return;

	last = NULL;
	p = q->head;
	while (p != NULL) {
		ret = f(p->element, vp);
		if (ret) {
			if (last) {
				last->next = p->next;
				if (last->next == NULL)
					q->tail = last;
			} else {
				q->head = p->next;
				if (q->head == NULL)
					q->tail = NULL;
			}

			temp = p;
			p = p->next;
			g(temp->element, vp);
			free(temp);
		} else {
			last = p;
			p = p->next;
		}
	}

	return;
}
