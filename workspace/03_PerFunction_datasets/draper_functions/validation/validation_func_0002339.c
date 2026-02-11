locks_free_lock_context(struct file_lock_context *ctx)
{
	if (ctx) {
		WARN_ON_ONCE(!list_empty(&ctx->flc_flock));
		WARN_ON_ONCE(!list_empty(&ctx->flc_posix));
		WARN_ON_ONCE(!list_empty(&ctx->flc_lease));
		kmem_cache_free(flctx_cache, ctx);
	}
}
