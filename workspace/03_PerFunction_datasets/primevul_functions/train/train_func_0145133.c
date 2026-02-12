xfs_bmap_btalloc_accounting(
	struct xfs_bmalloca	*ap,
	struct xfs_alloc_arg	*args)
{
	if (ap->flags & XFS_BMAPI_COWFORK) {


		if (ap->wasdel)
			return;


		ap->ip->i_delayed_blks += args->len;
		xfs_trans_mod_dquot_byino(ap->tp, ap->ip, XFS_TRANS_DQ_RES_BLKS,
				-(long)args->len);
		return;
	}


	ap->ip->i_d.di_nblocks += args->len;
	xfs_trans_log_inode(ap->tp, ap->ip, XFS_ILOG_CORE);
	if (ap->wasdel)
		ap->ip->i_delayed_blks -= args->len;
	xfs_trans_mod_dquot_byino(ap->tp, ap->ip,
		ap->wasdel ? XFS_TRANS_DQ_DELBCOUNT : XFS_TRANS_DQ_BCOUNT,
		args->len);
}
