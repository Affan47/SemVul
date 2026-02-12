static int ucma_close(struct inode *inode, struct file *filp)
{
	struct ucma_file *file = filp->private_data;


	while (!list_empty(&file->ctx_list)) {
		struct ucma_context *ctx = list_first_entry(
			&file->ctx_list, struct ucma_context, list);

		xa_erase(&ctx_table, ctx->id);
		__destroy_id(ctx);
	}
	kfree(file);
	return 0;
}
