static int io_poll_wake(struct wait_queue_entry *wait, unsigned mode, int sync,
			void *key)
{
	struct io_kiocb *req = wqe_to_req(wait);
	struct io_poll_iocb *poll = container_of(wait, struct io_poll_iocb,
						 wait);
	__poll_t mask = key_to_poll(key);

	if (unlikely(mask & POLLFREE)) {
		io_poll_mark_cancelled(req);

		io_poll_execute(req, 0, poll->events);


		list_del_init(&poll->wait.entry);


		smp_store_release(&poll->head, NULL);
		return 1;
	}


	if (mask && !(mask & poll->events))
		return 0;

	if (io_poll_get_ownership(req)) {

		if (mask && poll->events & EPOLLONESHOT) {
			list_del_init(&poll->wait.entry);
			poll->head = NULL;
			if (wqe_is_double(wait))
				req->flags &= ~REQ_F_DOUBLE_POLL;
			else
				req->flags &= ~REQ_F_SINGLE_POLL;
		}
		__io_poll_execute(req, mask, poll->events);
	}
	return 1;
}
