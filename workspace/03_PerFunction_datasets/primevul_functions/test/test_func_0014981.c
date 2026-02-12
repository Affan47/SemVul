int __mnt_want_write_file(struct file *file)
{
	if (file->f_mode & FMODE_WRITER) {


		if (__mnt_is_readonly(file->f_path.mnt))
			return -EROFS;
		return 0;
	}
	return __mnt_want_write(file->f_path.mnt);
}
