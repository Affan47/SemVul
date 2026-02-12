int sys_mknod(const char *path, mode_t mode, SMB_DEV_T dev)
{
#if defined(HAVE_MKNOD)
	return mknod(path, mode, dev);
#else

	errno = ENOSYS;
	return -1;
#endif
}
