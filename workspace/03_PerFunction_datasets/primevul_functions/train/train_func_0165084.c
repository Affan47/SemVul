static long do_tee(struct file *in, struct file *out, size_t len,
		   unsigned int flags)
{
	struct pipe_inode_info *ipipe = in->f_dentry->d_inode->i_pipe;
	struct pipe_inode_info *opipe = out->f_dentry->d_inode->i_pipe;
	int ret = -EINVAL;


	if (ipipe && opipe && ipipe != opipe) {


		ret = link_ipipe_prep(ipipe, flags);
		if (!ret) {
			ret = link_opipe_prep(opipe, flags);
			if (!ret) {
				ret = link_pipe(ipipe, opipe, len, flags);
				if (!ret && (flags & SPLICE_F_NONBLOCK))
					ret = -EAGAIN;
			}
		}
	}

	return ret;
}
