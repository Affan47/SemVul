iterate_dir(struct file *file, struct dir_context *ctx)
{
	struct inode *inode = file_inode(file);
	int res = -ENOTDIR;
	if (!file->f_op->iterate)
		goto out;

	res = security_file_permission(file, MAY_READ);
	if (res)
		goto out;

	res = mutex_lock_killable(&inode->i_mutex);
	if (res)
		goto out;

	res = -ENOENT;
	if (!IS_DEADDIR(inode)) {
		ctx->pos = file->f_pos;
		res = file->f_op->iterate(file, ctx);
		file->f_pos = ctx->pos;
		fsnotify_access(file);
		file_accessed(file);
	}
	mutex_unlock(&inode->i_mutex);
out:
	return res;
}
