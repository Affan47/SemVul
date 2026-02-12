xfs_attr_shortform_bytesfit(
	struct xfs_inode	*dp,
	int			bytes)
{
	struct xfs_mount	*mp = dp->i_mount;
	int64_t			dsize;
	int			minforkoff;
	int			maxforkoff;
	int			offset;


	offset = (XFS_LITINO(mp) - bytes) >> 3;

	if (dp->i_df.if_format == XFS_DINODE_FMT_DEV) {
		minforkoff = roundup(sizeof(xfs_dev_t), 8) >> 3;
		return (offset >= minforkoff) ? minforkoff : 0;
	}


	if (bytes <= XFS_IFORK_ASIZE(dp))
		return dp->i_d.di_forkoff;


	if (!(mp->m_flags & XFS_MOUNT_ATTR2))
		return 0;

	dsize = dp->i_df.if_bytes;

	switch (dp->i_df.if_format) {
	case XFS_DINODE_FMT_EXTENTS:


		if (!dp->i_d.di_forkoff && dp->i_df.if_bytes >
		    xfs_default_attroffset(dp))
			dsize = XFS_BMDR_SPACE_CALC(MINDBTPTRS);
		break;
	case XFS_DINODE_FMT_BTREE:


		if (dp->i_d.di_forkoff) {
			if (offset < dp->i_d.di_forkoff)
				return 0;
			return dp->i_d.di_forkoff;
		}
		dsize = XFS_BMAP_BROOT_SPACE(mp, dp->i_df.if_broot);
		break;
	}


	minforkoff = max_t(int64_t, dsize, XFS_BMDR_SPACE_CALC(MINDBTPTRS));
	minforkoff = roundup(minforkoff, 8) >> 3;


	maxforkoff = XFS_LITINO(mp) - XFS_BMDR_SPACE_CALC(MINABTPTRS);
	maxforkoff = maxforkoff >> 3;

	if (offset >= maxforkoff)
		return maxforkoff;
	if (offset >= minforkoff)
		return offset;
	return 0;
}
