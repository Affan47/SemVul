vfs_submount(const struct dentry *mountpoint, struct file_system_type *type,
	     const char *name, void *data)
{


	if (mountpoint->d_sb->s_user_ns != &init_user_ns)
		return ERR_PTR(-EPERM);

	return vfs_kern_mount(type, SB_SUBMOUNT, name, data);
}
