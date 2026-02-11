xfs_trans_mod_sb(
	xfs_trans_t	*tp,
	uint		field,
	int64_t		delta)
{
	uint32_t	flags = (XFS_TRANS_DIRTY|XFS_TRANS_SB_DIRTY);
	xfs_mount_t	*mp = tp->t_mountp;

	switch (field) {
	case XFS_TRANS_SB_ICOUNT:
		tp->t_icount_delta += delta;
		if (xfs_sb_version_haslazysbcount(&mp->m_sb))
			flags &= ~XFS_TRANS_SB_DIRTY;
		break;
	case XFS_TRANS_SB_IFREE:
		tp->t_ifree_delta += delta;
		if (xfs_sb_version_haslazysbcount(&mp->m_sb))
			flags &= ~XFS_TRANS_SB_DIRTY;
		break;
	case XFS_TRANS_SB_FDBLOCKS:


		if (delta < 0) {
			tp->t_blk_res_used += (uint)-delta;
			ASSERT(tp->t_blk_res_used <= tp->t_blk_res);
		}
		tp->t_fdblocks_delta += delta;
		if (xfs_sb_version_haslazysbcount(&mp->m_sb))
			flags &= ~XFS_TRANS_SB_DIRTY;
		break;
	case XFS_TRANS_SB_RES_FDBLOCKS:


		ASSERT(delta < 0);
		tp->t_res_fdblocks_delta += delta;
		if (xfs_sb_version_haslazysbcount(&mp->m_sb))
			flags &= ~XFS_TRANS_SB_DIRTY;
		break;
	case XFS_TRANS_SB_FREXTENTS:


		if (delta < 0) {
			tp->t_rtx_res_used += (uint)-delta;
			ASSERT(tp->t_rtx_res_used <= tp->t_rtx_res);
		}
		tp->t_frextents_delta += delta;
		break;
	case XFS_TRANS_SB_RES_FREXTENTS:


		ASSERT(delta < 0);
		tp->t_res_frextents_delta += delta;
		break;
	case XFS_TRANS_SB_DBLOCKS:
		ASSERT(delta > 0);
		tp->t_dblocks_delta += delta;
		break;
	case XFS_TRANS_SB_AGCOUNT:
		ASSERT(delta > 0);
		tp->t_agcount_delta += delta;
		break;
	case XFS_TRANS_SB_IMAXPCT:
		tp->t_imaxpct_delta += delta;
		break;
	case XFS_TRANS_SB_REXTSIZE:
		tp->t_rextsize_delta += delta;
		break;
	case XFS_TRANS_SB_RBMBLOCKS:
		tp->t_rbmblocks_delta += delta;
		break;
	case XFS_TRANS_SB_RBLOCKS:
		tp->t_rblocks_delta += delta;
		break;
	case XFS_TRANS_SB_REXTENTS:
		tp->t_rextents_delta += delta;
		break;
	case XFS_TRANS_SB_REXTSLOG:
		tp->t_rextslog_delta += delta;
		break;
	default:
		ASSERT(0);
		return;
	}

	tp->t_flags |= flags;
}
