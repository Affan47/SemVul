xfs_iunlink_remove(
	struct xfs_trans	*tp,
	struct xfs_inode	*ip)
{
	struct xfs_mount	*mp = tp->t_mountp;
	struct xfs_agi		*agi;
	struct xfs_buf		*agibp;
	struct xfs_buf		*last_ibp;
	struct xfs_dinode	*last_dip = NULL;
	xfs_agnumber_t		agno = XFS_INO_TO_AGNO(mp, ip->i_ino);
	xfs_agino_t		agino = XFS_INO_TO_AGINO(mp, ip->i_ino);
	xfs_agino_t		next_agino;
	xfs_agino_t		head_agino;
	short			bucket_index = agino % XFS_AGI_UNLINKED_BUCKETS;
	int			error;

	trace_xfs_iunlink_remove(ip);


	error = xfs_read_agi(mp, tp, agno, &agibp);
	if (error)
		return error;
	agi = agibp->b_addr;


	head_agino = be32_to_cpu(agi->agi_unlinked[bucket_index]);
	if (!xfs_verify_agino(mp, agno, head_agino)) {
		XFS_CORRUPTION_ERROR(__func__, XFS_ERRLEVEL_LOW, mp,
				agi, sizeof(*agi));
		return -EFSCORRUPTED;
	}


	error = xfs_iunlink_update_inode(tp, ip, agno, NULLAGINO, &next_agino);
	if (error)
		return error;


	if (next_agino != NULLAGINO) {
		error = xfs_iunlink_change_backref(agibp->b_pag, next_agino,
				NULLAGINO);
		if (error)
			return error;
	}

	if (head_agino != agino) {
		struct xfs_imap	imap;
		xfs_agino_t	prev_agino;


		error = xfs_iunlink_map_prev(tp, agno, head_agino, agino,
				&prev_agino, &imap, &last_dip, &last_ibp,
				agibp->b_pag);
		if (error)
			return error;


		xfs_iunlink_update_dinode(tp, agno, prev_agino, last_ibp,
				last_dip, &imap, next_agino);


		return xfs_iunlink_change_backref(agibp->b_pag, agino,
				next_agino);
	}


	return xfs_iunlink_update_bucket(tp, agno, agibp, bucket_index,
			next_agino);
}
