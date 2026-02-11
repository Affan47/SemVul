rt2x00queue_index_inc(struct queue_entry *entry, enum queue_index index)
{
	struct data_queue *queue = entry->queue;
	unsigned long irqflags;

	if (unlikely(index >= Q_INDEX_MAX)) {
		rt2x00_err(queue->rt2x00dev,
			   "Index change on invalid index type (%d)\n", index);
		return;
	}

	spin_lock_irqsave(&queue->index_lock, irqflags);

	queue->index[index]++;
	if (queue->index[index] >= queue->limit)
		queue->index[index] = 0;

	entry->last_action = jiffies;

	if (index == Q_INDEX) {
		queue->length++;
	} else if (index == Q_INDEX_DONE) {
		queue->length--;
		queue->count++;
	}

	spin_unlock_irqrestore(&queue->index_lock, irqflags);
}
