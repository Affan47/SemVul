static int ppp_open(struct inode *inode, struct file *file)
{
	cycle_kernel_lock();


	if (!capable(CAP_NET_ADMIN))
		return -EPERM;
	return 0;
}
