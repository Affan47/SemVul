static int __inode_security_revalidate(struct inode *inode,
				       struct dentry *dentry,
				       bool may_sleep)
{
	struct inode_security_struct *isec = selinux_inode(inode);

	might_sleep_if(may_sleep);

	if (selinux_initialized(&selinux_state) &&
	    isec->initialized != LABEL_INITIALIZED) {
		if (!may_sleep)
			return -ECHILD;


		inode_doinit_with_dentry(inode, dentry);
	}
	return 0;
}
