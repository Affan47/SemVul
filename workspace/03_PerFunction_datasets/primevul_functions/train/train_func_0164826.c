int permission(struct inode *inode, int mask, struct nameidata *nd)
{
	int retval, submask;
	struct vfsmount *mnt = NULL;

	if (nd)
		mnt = nd->path.mnt;

	if (mask & MAY_WRITE) {
		umode_t mode = inode->i_mode;


		if (IS_RDONLY(inode) &&
		    (S_ISREG(mode) || S_ISDIR(mode) || S_ISLNK(mode)))
			return -EROFS;


		if (IS_IMMUTABLE(inode))
			return -EACCES;
	}

	if ((mask & MAY_EXEC) && S_ISREG(inode->i_mode)) {


		if (mnt && (mnt->mnt_flags & MNT_NOEXEC))
			return -EACCES;
	}


	submask = mask & ~MAY_APPEND;
	if (inode->i_op && inode->i_op->permission) {
		retval = inode->i_op->permission(inode, submask, nd);
		if (!retval) {


			if ((mask & MAY_EXEC) && S_ISREG(inode->i_mode) &&
			    !(inode->i_mode & S_IXUGO))
				return -EACCES;
		}
	} else {
		retval = generic_permission(inode, submask, NULL);
	}
	if (retval)
		return retval;

	retval = devcgroup_inode_permission(inode, mask);
	if (retval)
		return retval;

	return security_inode_permission(inode, mask, nd);
}
