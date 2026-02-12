compat_sys_io_setup(unsigned nr_reqs, u32 __user *ctx32p)
{
	long ret;
	aio_context_t ctx64;

	mm_segment_t oldfs = get_fs();
	if (unlikely(get_user(ctx64, ctx32p)))
		return -EFAULT;

	set_fs(KERNEL_DS);

	ret = sys_io_setup(nr_reqs, (aio_context_t __user *) &ctx64);
	set_fs(oldfs);

	if (!ret)
		ret = put_user((u32) ctx64, ctx32p);
	return ret;
}
