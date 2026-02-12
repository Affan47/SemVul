xfs_finish_rename(
	struct xfs_trans	*tp)
{


	if (tp->t_mountp->m_flags & (XFS_MOUNT_WSYNC|XFS_MOUNT_DIRSYNC))
		xfs_trans_set_sync(tp);

	return xfs_trans_commit(tp);
}
