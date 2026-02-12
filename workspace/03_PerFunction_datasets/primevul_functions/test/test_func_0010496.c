static NTSTATUS vfswrap_notify_watch(vfs_handle_struct *vfs_handle,
				     struct sys_notify_context *ctx,
				     const char *path,
				     uint32_t *filter,
				     uint32_t *subdir_filter,
				     void (*callback)(struct sys_notify_context *ctx,
						      void *private_data,
						      struct notify_event *ev),
				     void *private_data, void *handle)
{


#ifdef HAVE_INOTIFY
	if (lp_kernel_change_notify(vfs_handle->conn->params)) {
		return inotify_watch(ctx, path, filter, subdir_filter,
				     callback, private_data, handle);
	}
#endif


	return NT_STATUS_OK;
}
