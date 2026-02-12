static long do_tee(struct file *in, struct file *out, size_t len,
		   unsigned int flags)
{
	struct pipe_inode_info *ipipe = pipe_info(in->f_path.dentry->d_inode);
	struct pipe_inode_info *opipe = pipe_info(out->f_path.dentry->d_inode);
	int ret = -EINVAL;


	if (ipipe && opipe && ipipe != opipe) {


		ret = link_ipipe_prep(ipipe, flags);
		if (!ret) {
			ret = link_opipe_prep(opipe, flags);
			if (!ret)
				ret = link_pipe(ipipe, opipe, len, flags);
		}
	}

	return ret;
}
