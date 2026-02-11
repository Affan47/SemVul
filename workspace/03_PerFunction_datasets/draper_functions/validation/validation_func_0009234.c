pvscsi_allocate_sg(struct pvscsi_adapter *adapter)
{
	struct pvscsi_ctx *ctx;
	int i;

	ctx = adapter->cmd_map;
	BUILD_BUG_ON(sizeof(struct pvscsi_sg_list) > SGL_SIZE);

	for (i = 0; i < adapter->req_depth; ++i, ++ctx) {
		ctx->sgl = (void *)__get_free_pages(GFP_KERNEL,
						    get_order(SGL_SIZE));
		ctx->sglPA = 0;
		BUG_ON(!IS_ALIGNED(((unsigned long)ctx->sgl), PAGE_SIZE));
		if (!ctx->sgl) {
			for (; i >= 0; --i, --ctx) {
				free_pages((unsigned long)ctx->sgl,
					   get_order(SGL_SIZE));
				ctx->sgl = NULL;
			}
			return -ENOMEM;
		}
	}

	return 0;
}
