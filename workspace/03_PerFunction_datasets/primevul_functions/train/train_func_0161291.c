xfs_fs_nr_cached_objects(
	struct super_block	*sb,
	struct shrink_control	*sc)
{

	if (WARN_ON_ONCE(!sb->s_fs_info))
		return 0;
	return xfs_reclaim_inodes_count(XFS_M(sb));
}
