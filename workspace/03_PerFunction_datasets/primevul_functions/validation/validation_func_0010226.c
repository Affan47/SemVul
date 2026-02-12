static inline struct io_uring_cqe *io_get_cqring(struct io_ring_ctx *ctx)
{
	struct io_rings *rings = ctx->rings;
	unsigned tail;


	if (__io_cqring_events(ctx) == rings->cq_ring_entries)
		return NULL;

	tail = ctx->cached_cq_tail++;
	return &rings->cqes[tail & ctx->cq_mask];
}
