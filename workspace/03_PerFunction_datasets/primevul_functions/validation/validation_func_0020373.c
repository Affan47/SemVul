static void io_ring_exit_work(struct work_struct *work)
{
	struct io_ring_ctx *ctx = container_of(work, struct io_ring_ctx,
					       exit_work);


	do {
		if (ctx->rings)
			io_cqring_overflow_flush(ctx, true);
		io_iopoll_try_reap_events(ctx);
	} while (!wait_for_completion_timeout(&ctx->ref_comp, HZ/20));
	io_ring_ctx_free(ctx);
}
