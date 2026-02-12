xfs_iunlink(
	struct xfs_trans	*tp,
	struct xfs_inode	*ip)
{
	struct xfs_mount	*mp = tp->t_mountp;
	struct xfs_agi		*agi;
	struct xfs_buf		*agibp;
	xfs_agino_t		next_agino;
	xfs_agnumber_t		agno = XFS_INO_TO_AGNO(mp, ip->i_ino);
	xfs_agino_t		agino = XFS_INO_TO_AGINO(mp, ip->i_ino);
	short			bucket_index = agino % XFS_AGI_UNLINKED_BUCKETS;
	int			error;

	ASSERT(VFS_I(ip)->i_nlink == 0);
	ASSERT(VFS_I(ip)->i_mode != 0);
	trace_xfs_iunlink(ip);


	error = xfs_read_agi(mp, tp, agno, &agibp);
	if (error)
		return error;
	agi = agibp->b_addr;


	next_agino = be32_to_cpu(agi->agi_unlinked[bucket_index]);
	if (next_agino == agino ||
	    !xfs_verify_agino_or_null(mp, agno, next_agino)) {
		xfs_buf_mark_corrupt(agibp);
		return -EFSCORRUPTED;
	}

	if (next_agino != NULLAGINO) {
		xfs_agino_t		old_agino;


		error = xfs_iunlink_update_inode(tp, ip, agno, next_agino,
				&old_agino);
		if (error)
			return error;
		ASSERT(old_agino == NULLAGINO);


		error = xfs_iunlink_add_backref(agibp->b_pag, agino, next_agino);
		if (error)
			return error;
	}


	return xfs_iunlink_update_bucket(tp, agno, agibp, bucket_index, agino);
}
