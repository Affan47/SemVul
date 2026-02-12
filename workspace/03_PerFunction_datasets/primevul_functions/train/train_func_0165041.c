asmlinkage long sys_ftruncate(unsigned int fd, unsigned long length)
{
	long ret = do_sys_ftruncate(fd, length, 1);

	prevent_tail_call(ret);
	return ret;
}
