ssize_t splice_direct_to_actor(struct file *in, struct splice_desc *sd,
			       splice_direct_actor *actor)
{
	struct pipe_inode_info *pipe;
	long ret, bytes;
	umode_t i_mode;
	size_t len;
	int i, flags;


	i_mode = in->f_path.dentry->d_inode->i_mode;
	if (unlikely(!S_ISREG(i_mode) && !S_ISBLK(i_mode)))
		return -EINVAL;


	pipe = current->splice_pipe;
	if (unlikely(!pipe)) {
		pipe = alloc_pipe_info(NULL);
		if (!pipe)
			return -ENOMEM;


		pipe->readers = 1;

		current->splice_pipe = pipe;
	}


	ret = 0;
	bytes = 0;
	len = sd->total_len;
	flags = sd->flags;


	sd->flags &= ~SPLICE_F_NONBLOCK;

	while (len) {
		size_t read_len;
		loff_t pos = sd->pos;

		ret = do_splice_to(in, &pos, pipe, len, flags);
		if (unlikely(ret <= 0))
			goto out_release;

		read_len = ret;
		sd->total_len = read_len;


		ret = actor(pipe, sd);
		if (unlikely(ret <= 0))
			goto out_release;

		bytes += ret;
		len -= ret;
		sd->pos = pos;

		if (ret < read_len)
			goto out_release;
	}

	pipe->nrbufs = pipe->curbuf = 0;
	return bytes;

out_release:


	for (i = 0; i < PIPE_BUFFERS; i++) {
		struct pipe_buffer *buf = pipe->bufs + i;

		if (buf->ops) {
			buf->ops->release(pipe, buf);
			buf->ops = NULL;
		}
	}
	pipe->nrbufs = pipe->curbuf = 0;


	if (bytes > 0)
		return bytes;

	return ret;

}
