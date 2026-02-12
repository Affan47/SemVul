static int io_poll_update(struct io_kiocb *req, unsigned int issue_flags)
{
	struct io_ring_ctx *ctx = req->ctx;
	struct io_kiocb *preq;
	bool completing;
	int ret;

	spin_lock_irq(&ctx->completion_lock);
	preq = io_poll_find(ctx, req->poll_update.old_user_data, true);
	if (!preq) {
		ret = -ENOENT;
		goto err;
	}

	if (!req->poll_update.update_events && !req->poll_update.update_user_data) {
		completing = true;
		ret = io_poll_remove_one(preq) ? 0 : -EALREADY;
		goto err;
	}


	completing = !__io_poll_remove_one(preq, &preq->poll, false);
	if (completing && (preq->poll.events & EPOLLONESHOT)) {
		ret = -EALREADY;
		goto err;
	}

	ret = 0;
err:
	if (ret < 0) {
		spin_unlock_irq(&ctx->completion_lock);
		req_set_fail_links(req);
		io_req_complete(req, ret);
		return 0;
	}

	if (req->poll_update.update_events) {
		preq->poll.events &= ~0xffff;
		preq->poll.events |= req->poll_update.events & 0xffff;
		preq->poll.events |= IO_POLL_UNMASK;
	}
	if (req->poll_update.update_user_data)
		preq->user_data = req->poll_update.new_user_data;
	spin_unlock_irq(&ctx->completion_lock);


	io_req_complete(req, ret);

	if (!completing) {
		ret = io_poll_add(preq, issue_flags);
		if (ret < 0) {
			req_set_fail_links(preq);
			io_req_complete(preq, ret);
		}
	}
	return 0;
}
