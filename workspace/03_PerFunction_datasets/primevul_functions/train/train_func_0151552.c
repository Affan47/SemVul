static void context_close(struct i915_gem_context *ctx)
{
	i915_gem_context_set_closed(ctx);


	release_hw_id(ctx);


	lut_close(ctx);
	if (ctx->ppgtt)
		i915_ppgtt_close(&ctx->ppgtt->vm);

	ctx->file_priv = ERR_PTR(-EBADF);
	i915_gem_context_put(ctx);
}
