static int io_submit_sqe(struct io_ring_ctx *ctx, struct io_kiocb *req,
			 const struct io_uring_sqe *sqe)
{
	struct io_submit_link *link = &ctx->submit_state.link;
	int ret;

	ret = io_init_req(ctx, req, sqe);
	if (unlikely(ret)) {
fail_req:
		if (link->head) {

			link->head->flags |= REQ_F_FAIL_LINK;
			io_req_complete_failed(link->head, -ECANCELED);
			link->head = NULL;
		}
		io_req_complete_failed(req, ret);
		return ret;
	}
	ret = io_req_prep(req, sqe);
	if (unlikely(ret))
		goto fail_req;


	trace_io_uring_submit_sqe(ctx, req->opcode, req->user_data,
				true, ctx->flags & IORING_SETUP_SQPOLL);


	if (link->head) {
		struct io_kiocb *head = link->head;


		if (req->flags & REQ_F_IO_DRAIN) {
			head->flags |= REQ_F_IO_DRAIN;
			ctx->drain_next = 1;
		}
		ret = io_req_prep_async(req);
		if (unlikely(ret))
			goto fail_req;
		trace_io_uring_link(ctx, req, head);
		link->last->link = req;
		link->last = req;


		if (!(req->flags & (REQ_F_LINK | REQ_F_HARDLINK))) {
			io_queue_sqe(head);
			link->head = NULL;
		}
	} else {
		if (unlikely(ctx->drain_next)) {
			req->flags |= REQ_F_IO_DRAIN;
			ctx->drain_next = 0;
		}
		if (req->flags & (REQ_F_LINK | REQ_F_HARDLINK)) {
			link->head = req;
			link->last = req;
		} else {
			io_queue_sqe(req);
		}
	}

	return 0;
}
