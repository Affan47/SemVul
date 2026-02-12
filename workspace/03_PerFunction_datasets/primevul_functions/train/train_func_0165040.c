asmlinkage long sys_truncate(const char __user * path, unsigned long length)
{

	return do_sys_truncate(path, (long)length);
}
