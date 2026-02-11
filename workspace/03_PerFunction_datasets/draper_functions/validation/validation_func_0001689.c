xpc_put_fifo_entry_uv(struct xpc_fifo_head_uv *head,
		      struct xpc_fifo_entry_uv *last)
{
	unsigned long irq_flags;

	last->next = NULL;
	spin_lock_irqsave(&head->lock, irq_flags);
	if (head->last != NULL)
		head->last->next = last;
	else
		head->first = last;
	head->last = last;
	head->n_entries++;
	spin_unlock_irqrestore(&head->lock, irq_flags);
}
