static int selinux_inode_removexattr(struct dentry *dentry, const char *name)
{
	if (strcmp(name, XATTR_NAME_SELINUX)) {
		int rc = cap_inode_removexattr(dentry, name);
		if (rc)
			return rc;


		return dentry_has_perm(current_cred(), dentry, FILE__SETATTR);
	}


	return -EACCES;
}
