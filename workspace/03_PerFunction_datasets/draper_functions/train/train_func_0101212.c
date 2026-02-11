iwl_queue_space(const struct iwl_queue *q)
{
	unsigned int max;
	unsigned int used;


	if (q->n_window < TFD_QUEUE_SIZE_MAX)
		max = q->n_window;
	else
		max = TFD_QUEUE_SIZE_MAX - 1;


	used = (q->write_ptr - q->read_ptr) & (TFD_QUEUE_SIZE_MAX - 1);

	if (WARN_ON(used > max))
		return 0;

	return max - used;
}
