static int vfswrap_chmod(vfs_handle_struct *handle, const char *path, mode_t mode)
{
	int result;

	START_PROFILE(syscall_chmod);


	{
		int saved_errno = errno;
		if ((result = SMB_VFS_CHMOD_ACL(handle->conn, path, mode)) == 0) {
			END_PROFILE(syscall_chmod);
			return result;
		}

		errno = saved_errno;
	}

	result = chmod(path, mode);
	END_PROFILE(syscall_chmod);
	return result;
}
