static inline unsigned int io_put_kbuf(struct io_kiocb *req,
				       unsigned issue_flags)
{
	unsigned int cflags;

	if (likely(!(req->flags & REQ_F_BUFFER_SELECTED)))
		return 0;


	if (issue_flags & IO_URING_F_UNLOCKED) {
		struct io_ring_ctx *ctx = req->ctx;

		spin_lock(&ctx->completion_lock);
		cflags = __io_put_kbuf(req, &ctx->io_buffers_comp);
		spin_unlock(&ctx->completion_lock);
	} else {
		lockdep_assert_held(&req->ctx->uring_lock);

		cflags = __io_put_kbuf(req, &req->ctx->io_buffers_cache);
	}

	return cflags;
}
