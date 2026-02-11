cb_tree_walk(
	const char *root, const git_tree_entry *entry, void *payload)
{
	int error;
	struct tree_walk_context *ctx = payload;


	if (git_tree_entry_type(entry) == GIT_OBJ_COMMIT)
		return 0;

	if (!(error = git_buf_sets(&ctx->buf, root)) &&
		!(error = git_buf_puts(&ctx->buf, git_tree_entry_name(entry))))
		error = git_packbuilder_insert(
			ctx->pb, git_tree_entry_id(entry), git_buf_cstr(&ctx->buf));

	return error;
}
