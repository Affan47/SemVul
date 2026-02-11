ffile_writeto(int fd, const void *buff, size_t size, off_t offset)
{
	if (lseek(fd, offset, SEEK_SET) != offset)
	{
#ifdef CAVAN_DEBUG
		pr_error_info("lseek");
#endif
		return -EFAULT;
	}

	return ffile_write(fd, buff, size);
}
