xfs_fileattr_set(
	struct user_namespace	*mnt_userns,
	struct dentry		*dentry,
	struct fileattr		*fa)
{
	struct xfs_inode	*ip = XFS_I(d_inode(dentry));
	struct xfs_mount	*mp = ip->i_mount;
	struct xfs_trans	*tp;
	struct xfs_dquot	*pdqp = NULL;
	struct xfs_dquot	*olddquot = NULL;
	int			error;

	trace_xfs_ioctl_setattr(ip);

	if (d_is_special(dentry))
		return -ENOTTY;

	if (!fa->fsx_valid) {
		if (fa->flags & ~(FS_IMMUTABLE_FL | FS_APPEND_FL |
				  FS_NOATIME_FL | FS_NODUMP_FL |
				  FS_SYNC_FL | FS_DAX_FL | FS_PROJINHERIT_FL))
			return -EOPNOTSUPP;
	}

	error = xfs_ioctl_setattr_check_projid(ip, fa);
	if (error)
		return error;


	if (fa->fsx_valid && XFS_IS_QUOTA_ON(mp)) {
		error = xfs_qm_vop_dqalloc(ip, VFS_I(ip)->i_uid,
				VFS_I(ip)->i_gid, fa->fsx_projid,
				XFS_QMOPT_PQUOTA, NULL, NULL, &pdqp);
		if (error)
			return error;
	}

	xfs_ioctl_setattr_prepare_dax(ip, fa);

	tp = xfs_ioctl_setattr_get_trans(ip, pdqp);
	if (IS_ERR(tp)) {
		error = PTR_ERR(tp);
		goto error_free_dquots;
	}

	error = xfs_ioctl_setattr_check_extsize(ip, fa);
	if (error)
		goto error_trans_cancel;

	error = xfs_ioctl_setattr_check_cowextsize(ip, fa);
	if (error)
		goto error_trans_cancel;

	error = xfs_ioctl_setattr_xflags(tp, ip, fa);
	if (error)
		goto error_trans_cancel;

	if (!fa->fsx_valid)
		goto skip_xattr;


	if ((VFS_I(ip)->i_mode & (S_ISUID|S_ISGID)) &&
	    !capable_wrt_inode_uidgid(mnt_userns, VFS_I(ip), CAP_FSETID))
		VFS_I(ip)->i_mode &= ~(S_ISUID|S_ISGID);


	if (ip->i_projid != fa->fsx_projid) {
		if (XFS_IS_PQUOTA_ON(mp)) {
			olddquot = xfs_qm_vop_chown(tp, ip,
						&ip->i_pdquot, pdqp);
		}
		ip->i_projid = fa->fsx_projid;
	}


	if (ip->i_diflags & (XFS_DIFLAG_EXTSIZE | XFS_DIFLAG_EXTSZINHERIT))
		ip->i_extsize = XFS_B_TO_FSB(mp, fa->fsx_extsize);
	else
		ip->i_extsize = 0;

	if (xfs_has_v3inodes(mp)) {
		if (ip->i_diflags2 & XFS_DIFLAG2_COWEXTSIZE)
			ip->i_cowextsize = XFS_B_TO_FSB(mp, fa->fsx_cowextsize);
		else
			ip->i_cowextsize = 0;
	}

skip_xattr:
	error = xfs_trans_commit(tp);


	xfs_qm_dqrele(olddquot);
	xfs_qm_dqrele(pdqp);

	return error;

error_trans_cancel:
	xfs_trans_cancel(tp);
error_free_dquots:
	xfs_qm_dqrele(pdqp);
	return error;
}
