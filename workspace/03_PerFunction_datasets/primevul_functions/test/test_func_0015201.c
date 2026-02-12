static int io_wake_function(struct wait_queue_entry *curr, unsigned int mode,
			    int wake_flags, void *key)
{
	struct io_wait_queue *iowq = container_of(curr, struct io_wait_queue,
							wq);


	if (io_should_wake(iowq) || test_bit(0, &iowq->ctx->check_cq_overflow))
		return autoremove_wake_function(curr, mode, wake_flags, key);
	return -1;
}
