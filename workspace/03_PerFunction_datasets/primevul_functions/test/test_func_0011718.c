static int selinux_inode_getsecurity(struct user_namespace *mnt_userns,
				     struct inode *inode, const char *name,
				     void **buffer, bool alloc)
{
	u32 size;
	int error;
	char *context = NULL;
	struct inode_security_struct *isec;


	if (!selinux_initialized(&selinux_state) ||
	    strcmp(name, XATTR_SELINUX_SUFFIX))
		return -EOPNOTSUPP;


	isec = inode_security(inode);
	if (has_cap_mac_admin(false))
		error = security_sid_to_context_force(&selinux_state,
						      isec->sid, &context,
						      &size);
	else
		error = security_sid_to_context(&selinux_state, isec->sid,
						&context, &size);
	if (error)
		return error;
	error = size;
	if (alloc) {
		*buffer = context;
		goto out_nofree;
	}
	kfree(context);
out_nofree:
	return error;
}
