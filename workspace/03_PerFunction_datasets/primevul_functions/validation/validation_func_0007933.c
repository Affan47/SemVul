static int may_linkat(struct path *link)
{
	struct inode *inode = link->dentry->d_inode;


	if (!uid_valid(inode->i_uid) || !gid_valid(inode->i_gid))
		return -EOVERFLOW;

	if (!sysctl_protected_hardlinks)
		return 0;


	if (safe_hardlink_source(inode) || inode_owner_or_capable(inode))
		return 0;

	audit_log_path_denied(AUDIT_ANOM_LINK, "linkat");
	return -EPERM;
}
