static bool io_drain_req(struct io_kiocb *req)
{
	struct io_kiocb *pos;
	struct io_ring_ctx *ctx = req->ctx;
	struct io_defer_entry *de;
	int ret;
	u32 seq;


	if (ctx->drain_next) {
		req->flags |= REQ_F_IO_DRAIN;
		ctx->drain_next = false;
	}

	io_for_each_link(pos, req->link) {
		if (pos->flags & REQ_F_IO_DRAIN) {
			ctx->drain_next = true;
			req->flags |= REQ_F_IO_DRAIN;
			break;
		}
	}


	if (likely(list_empty_careful(&ctx->defer_list) &&
		!(req->flags & REQ_F_IO_DRAIN))) {
		ctx->drain_active = false;
		return false;
	}

	seq = io_get_sequence(req);

	if (!req_need_defer(req, seq) && list_empty_careful(&ctx->defer_list))
		return false;

	ret = io_req_prep_async(req);
	if (ret)
		return ret;
	io_prep_async_link(req);
	de = kmalloc(sizeof(*de), GFP_KERNEL);
	if (!de) {
		io_req_complete_failed(req, -ENOMEM);
		return true;
	}

	spin_lock_irq(&ctx->completion_lock);
	if (!req_need_defer(req, seq) && list_empty(&ctx->defer_list)) {
		spin_unlock_irq(&ctx->completion_lock);
		kfree(de);
		io_queue_async_work(req);
		return true;
	}

	trace_io_uring_defer(ctx, req, req->user_data);
	de->req = req;
	de->seq = seq;
	list_add_tail(&de->list, &ctx->defer_list);
	spin_unlock_irq(&ctx->completion_lock);
	return true;
}
