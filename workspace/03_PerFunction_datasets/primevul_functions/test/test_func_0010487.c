static int vfswrap_set_offline(struct vfs_handle_struct *handle,
			       const struct smb_filename *fname)
{

#if defined(ENOTSUP)
	errno = ENOTSUP;
#endif
	return -1;
}
