isl_blk_clear_cache(struct isl_ctx *ctx)
{
	int i;

	for (i = 0; i < ctx->n_cached; ++i)
		isl_blk_free_force(ctx, ctx->cache[i]);
	ctx->n_cached = 0;
}
