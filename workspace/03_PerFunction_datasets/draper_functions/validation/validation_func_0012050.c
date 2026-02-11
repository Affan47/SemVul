dequeue_mad(struct ib_mad_list_head *mad_list)
{
	struct ib_mad_queue *mad_queue;
	unsigned long flags;

	BUG_ON(!mad_list->mad_queue);
	mad_queue = mad_list->mad_queue;
	spin_lock_irqsave(&mad_queue->lock, flags);
	list_del(&mad_list->list);
	mad_queue->count--;
	spin_unlock_irqrestore(&mad_queue->lock, flags);
}
