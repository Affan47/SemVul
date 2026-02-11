irmo_queue_free(IrmoQueue *queue)
{


	while (!irmo_queue_is_empty(queue)) {
		irmo_queue_pop_head(queue);
	}


	free(queue);
}
