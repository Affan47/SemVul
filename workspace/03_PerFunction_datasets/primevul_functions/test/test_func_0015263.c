const struct io_uring_sqe *sqe)
	__must_hold(&ctx->uring_lock)
{
	struct io_submit_link *link = &ctx->submit_state.link;
	int ret;

	ret = io_init_req(ctx, req, sqe);
	if (unlikely(ret)) {
		trace_io_uring_req_failed(sqe, ctx, req, ret);


		if (link->head) {


			if (!(link->head->flags & REQ_F_FAIL))
				req_fail_link_node(link->head, -ECANCELED);
		} else if (!(req->flags & (REQ_F_LINK | REQ_F_HARDLINK))) {


			io_req_complete_failed(req, ret);
			return ret;
		}
		req_fail_link_node(req, ret);
	}


	trace_io_uring_submit_sqe(ctx, req, req->user_data, req->opcode,
				  req->flags, true,
				  ctx->flags & IORING_SETUP_SQPOLL);


	if (link->head) {
		struct io_kiocb *head = link->head;

		if (!(req->flags & REQ_F_FAIL)) {
			ret = io_req_prep_async(req);
			if (unlikely(ret)) {
				req_fail_link_node(req, ret);
				if (!(head->flags & REQ_F_FAIL))
					req_fail_link_node(head, -ECANCELED);
			}
		}
		trace_io_uring_link(ctx, req, head);
		link->last->link = req;
		link->last = req;

		if (req->flags & (REQ_F_LINK | REQ_F_HARDLINK))
			return 0;

		link->head = NULL;
		req = head;
	} else if (req->flags & (REQ_F_LINK | REQ_F_HARDLINK)) {
		link->head = req;
		link->last = req;
		return 0;
	}

	io_queue_sqe(req);
	return 0;
}
