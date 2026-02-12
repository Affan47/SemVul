xfs_bmap_add_attrfork_local(
	xfs_trans_t		*tp,
	xfs_inode_t		*ip,
	xfs_fsblock_t		*firstblock,
	struct xfs_defer_ops	*dfops,
	int			*flags)
{
	xfs_da_args_t		dargs;

	if (ip->i_df.if_bytes <= XFS_IFORK_DSIZE(ip))
		return 0;

	if (S_ISDIR(VFS_I(ip)->i_mode)) {
		memset(&dargs, 0, sizeof(dargs));
		dargs.geo = ip->i_mount->m_dir_geo;
		dargs.dp = ip;
		dargs.firstblock = firstblock;
		dargs.dfops = dfops;
		dargs.total = dargs.geo->fsbcount;
		dargs.whichfork = XFS_DATA_FORK;
		dargs.trans = tp;
		return xfs_dir2_sf_to_block(&dargs);
	}

	if (S_ISLNK(VFS_I(ip)->i_mode))
		return xfs_bmap_local_to_extents(tp, ip, firstblock, 1,
						 flags, XFS_DATA_FORK,
						 xfs_symlink_local_to_remote);


	ASSERT(0);
	return -EFSCORRUPTED;
}
