static int fastrpc_internal_invoke(struct fastrpc_user *fl,  u32 kernel,
				   u32 handle, u32 sc,
				   struct fastrpc_invoke_args *args)
{
	struct fastrpc_invoke_ctx *ctx = NULL;
	int err = 0;

	if (!fl->sctx)
		return -EINVAL;

	if (!fl->cctx->rpdev)
		return -EPIPE;

	ctx = fastrpc_context_alloc(fl, kernel, sc, args);
	if (IS_ERR(ctx))
		return PTR_ERR(ctx);

	if (ctx->nscalars) {
		err = fastrpc_get_args(kernel, ctx);
		if (err)
			goto bail;
	}


	dma_wmb();

	err = fastrpc_invoke_send(fl->sctx, ctx, kernel, handle);
	if (err)
		goto bail;


	err = wait_for_completion_interruptible(&ctx->work);
	if (err)
		goto bail;


	err = ctx->retval;
	if (err)
		goto bail;

	if (ctx->nscalars) {

		dma_rmb();

		err = fastrpc_put_args(ctx, kernel);
		if (err)
			goto bail;
	}

bail:

	spin_lock(&fl->lock);
	list_del(&ctx->node);
	spin_unlock(&fl->lock);
	fastrpc_context_put(ctx);

	if (err)
		dev_dbg(fl->sctx->dev, "Error: Invoke Failed %d\n", err);

	return err;
}
