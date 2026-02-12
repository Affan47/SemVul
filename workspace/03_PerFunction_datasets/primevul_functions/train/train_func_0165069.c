asmlinkage long sys_faccessat(int dfd, const char __user *filename, int mode)
{
	struct nameidata nd;
	int old_fsuid, old_fsgid;
	kernel_cap_t old_cap;
	int res;

	if (mode & ~S_IRWXO)
		return -EINVAL;

	old_fsuid = current->fsuid;
	old_fsgid = current->fsgid;
	old_cap = current->cap_effective;

	current->fsuid = current->uid;
	current->fsgid = current->gid;


	if (current->uid)
		cap_clear(current->cap_effective);
	else
		current->cap_effective = current->cap_permitted;

	res = __user_walk_fd(dfd, filename, LOOKUP_FOLLOW|LOOKUP_ACCESS, &nd);
	if (res)
		goto out;

	res = vfs_permission(&nd, mode);

	if(res || !(mode & S_IWOTH) ||
	   special_file(nd.dentry->d_inode->i_mode))
		goto out_path_release;

	if(IS_RDONLY(nd.dentry->d_inode))
		res = -EROFS;

out_path_release:
	path_release(&nd);
out:
	current->fsuid = old_fsuid;
	current->fsgid = old_fsgid;
	current->cap_effective = old_cap;

	return res;
}
