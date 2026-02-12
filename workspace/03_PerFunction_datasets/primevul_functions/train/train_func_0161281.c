xfs_fs_drop_inode(
	struct inode		*inode)
{
	struct xfs_inode	*ip = XFS_I(inode);


	if (ip->i_flags & XFS_IRECOVERY) {
		ASSERT(ip->i_mount->m_log->l_flags & XLOG_RECOVERY_NEEDED);
		return 0;
	}

	return generic_drop_inode(inode) || (ip->i_flags & XFS_IDONTCACHE);
}
