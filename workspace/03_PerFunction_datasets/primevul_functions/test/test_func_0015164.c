static inline void io_commit_cqring(struct io_ring_ctx *ctx)
{

	smp_store_release(&ctx->rings->cq.tail, ctx->cached_cq_tail);
}
