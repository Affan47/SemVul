long do_splice_direct(struct file *in, loff_t *ppos, struct file *out,
		      size_t len, unsigned int flags)
{
	struct pipe_inode_info *pipe;
	long ret, bytes;
	loff_t out_off;
	umode_t i_mode;
	int i;


	i_mode = in->f_dentry->d_inode->i_mode;
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
	out_off = 0;

	while (len) {
		size_t read_len, max_read_len;


		max_read_len = min(len, (size_t)(PIPE_BUFFERS*PAGE_SIZE));

		ret = do_splice_to(in, ppos, pipe, max_read_len, flags);
		if (unlikely(ret < 0))
			goto out_release;

		read_len = ret;


		ret = do_splice_from(pipe, out, &out_off, read_len,
				     flags & ~SPLICE_F_NONBLOCK);
		if (unlikely(ret < 0))
			goto out_release;

		bytes += ret;
		len -= ret;


		if ((flags & SPLICE_F_NONBLOCK) && (read_len < max_read_len))
			break;
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
