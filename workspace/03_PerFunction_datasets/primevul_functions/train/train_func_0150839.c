xfs_attr3_leaf_freextent(
	struct xfs_trans	**trans,
	struct xfs_inode	*dp,
	xfs_dablk_t		blkno,
	int			blkcnt)
{
	struct xfs_bmbt_irec	map;
	struct xfs_buf		*bp;
	xfs_dablk_t		tblkno;
	xfs_daddr_t		dblkno;
	int			tblkcnt;
	int			dblkcnt;
	int			nmap;
	int			error;


	tblkno = blkno;
	tblkcnt = blkcnt;
	while (tblkcnt > 0) {


		nmap = 1;
		error = xfs_bmapi_read(dp, (xfs_fileoff_t)tblkno, tblkcnt,
				       &map, &nmap, XFS_BMAPI_ATTRFORK);
		if (error) {
			return(error);
		}
		ASSERT(nmap == 1);
		ASSERT(map.br_startblock != DELAYSTARTBLOCK);


		if (map.br_startblock != HOLESTARTBLOCK) {

			dblkno = XFS_FSB_TO_DADDR(dp->i_mount,
						  map.br_startblock);
			dblkcnt = XFS_FSB_TO_BB(dp->i_mount,
						map.br_blockcount);
			bp = xfs_trans_get_buf(*trans,
					dp->i_mount->m_ddev_targp,
					dblkno, dblkcnt, 0);
			if (!bp)
				return ENOMEM;
			xfs_trans_binval(*trans, bp);


			error = xfs_trans_roll(trans, dp);
			if (error)
				return (error);
		}

		tblkno += map.br_blockcount;
		tblkcnt -= map.br_blockcount;
	}

	return(0);
}
