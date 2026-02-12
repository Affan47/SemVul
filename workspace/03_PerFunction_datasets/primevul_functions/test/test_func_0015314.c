static inline void io_cqring_wake(struct io_ring_ctx *ctx)
{


	if (wq_has_sleeper(&ctx->cq_wait))
		wake_up_all(&ctx->cq_wait);
}
