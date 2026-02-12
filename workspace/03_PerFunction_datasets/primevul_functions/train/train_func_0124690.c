xfs_alloc_pagf_init(
	xfs_mount_t		*mp,
	xfs_trans_t		*tp,
	xfs_agnumber_t		agno,
	int			flags)
{
	xfs_buf_t		*bp;
	int			error;

	error = xfs_alloc_read_agf(mp, tp, agno, flags, &bp);
	if (!error)
		xfs_trans_brelse(tp, bp);
	return error;
}
