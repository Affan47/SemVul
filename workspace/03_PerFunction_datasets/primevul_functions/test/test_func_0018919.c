static int io_submit_sqe(struct io_ring_ctx *ctx, struct io_kiocb *req,
			 const struct io_uring_sqe *sqe)
{
	struct io_submit_link *link = &ctx->submit_state.link;
	int ret;

	ret = io_init_req(ctx, req, sqe);
	if (unlikely(ret)) {
fail_req:
		if (link->head) {

			req_set_fail(link->head);
			io_req_complete_failed(link->head, -ECANCELED);
			link->head = NULL;
		}
		io_req_complete_failed(req, ret);
		return ret;
	}

	ret = io_req_prep(req, sqe);
	if (unlikely(ret))
		goto fail_req;


	trace_io_uring_submit_sqe(ctx, req, req->opcode, req->user_data,
				  req->flags, true,
				  ctx->flags & IORING_SETUP_SQPOLL);


	if (link->head) {
		struct io_kiocb *head = link->head;

		ret = io_req_prep_async(req);
		if (unlikely(ret))
			goto fail_req;
		trace_io_uring_link(ctx, req, head);
		link->last->link = req;
		link->last = req;


		if (!(req->flags & (REQ_F_LINK | REQ_F_HARDLINK))) {
			link->head = NULL;
			io_queue_sqe(head);
		}
	} else {
		if (req->flags & (REQ_F_LINK | REQ_F_HARDLINK)) {
			link->head = req;
			link->last = req;
		} else {
			io_queue_sqe(req);
		}
	}

	return 0;
}
