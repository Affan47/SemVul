sci_get_from_queue(sci_queue_t *queue, int *type)
{
	sci_queue_node_t *node = queue->end;
	if (node) {
		void *retval = node->data;
		if (type)
			*type = node->type;

		queue->end = node->next;

		if (queue->end == NULL)
			queue->start = NULL;

		free(node);
		return retval;
	}
	return NULL;
}
