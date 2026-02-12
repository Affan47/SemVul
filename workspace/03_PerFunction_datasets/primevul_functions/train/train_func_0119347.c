static int __destroy_id(struct ucma_context *ctx)
{


	if (refcount_inc_not_zero(&ctx->ref)) {
		rdma_lock_handler(ctx->cm_id);
		ctx->destroying = 1;
		rdma_unlock_handler(ctx->cm_id);
		ucma_put_ctx(ctx);
	}

	cancel_work_sync(&ctx->close_work);

	if (ctx->cm_id)
		ucma_close_id(&ctx->close_work);
	return ucma_free_ctx(ctx);
}
