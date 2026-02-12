xfs_quiesce_attr(
	struct xfs_mount	*mp)
{
	int	error = 0;


	while (atomic_read(&mp->m_active_trans) > 0)
		delay(100);


	xfs_log_force(mp, XFS_LOG_SYNC);


	xfs_reclaim_inodes(mp, 0);
	xfs_reclaim_inodes(mp, SYNC_WAIT);


	error = xfs_log_sbcount(mp);
	if (error)
		xfs_warn(mp, "xfs_attr_quiesce: failed to log sb changes. "
				"Frozen image may not be consistent.");


	WARN_ON(atomic_read(&mp->m_active_trans) != 0);

	xfs_log_quiesce(mp);
}
