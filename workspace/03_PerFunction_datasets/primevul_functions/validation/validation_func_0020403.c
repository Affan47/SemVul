static int io_poll_double_wake(struct wait_queue_entry *wait, unsigned mode,
			       int sync, void *key)
{
	struct io_kiocb *req = wait->private;
	struct io_poll_iocb *poll = req->apoll->double_poll;
	__poll_t mask = key_to_poll(key);


	if (mask && !(mask & poll->events))
		return 0;

	if (poll && poll->head) {
		bool done;

		spin_lock(&poll->head->lock);
		done = list_empty(&poll->wait.entry);
		if (!done)
			list_del_init(&poll->wait.entry);
		spin_unlock(&poll->head->lock);
		if (!done)
			__io_async_wake(req, poll, mask, io_poll_task_func);
	}
	refcount_dec(&req->refs);
	return 1;
}
