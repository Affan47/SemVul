ssize_t splice_from_pipe(struct pipe_inode_info *pipe, struct file *out,
			 loff_t *ppos, size_t len, unsigned int flags,
			 splice_actor *actor)
{
	ssize_t ret;
	struct inode *inode = out->f_mapping->host;


	inode_double_lock(inode, pipe->inode);
	ret = __splice_from_pipe(pipe, out, ppos, len, flags, actor);
	inode_double_unlock(inode, pipe->inode);

	return ret;
}
