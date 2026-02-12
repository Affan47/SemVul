static off_t vfswrap_lseek(vfs_handle_struct *handle, files_struct *fsp, off_t offset, int whence)
{
	off_t result = 0;

	START_PROFILE(syscall_lseek);


	if (fsp->fh->fd != -1)
		result = lseek(fsp->fh->fd, offset, whence);


	if((result == -1) && (errno == ESPIPE)) {
		result = 0;
		errno = 0;
	}

	END_PROFILE(syscall_lseek);
	return result;
}
