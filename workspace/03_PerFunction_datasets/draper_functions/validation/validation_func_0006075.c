xfs_btree_del_cursor(
	xfs_btree_cur_t	*cur,
	int		error)
{
	int		i;


	for (i = 0; i < cur->bc_nlevels; i++) {
		if (cur->bc_bufs[i])
			xfs_trans_brelse(cur->bc_tp, cur->bc_bufs[i]);
		else if (!error)
			break;
	}


	ASSERT(cur->bc_btnum != XFS_BTNUM_BMAP ||
	       cur->bc_private.b.allocated == 0);


	kmem_zone_free(xfs_btree_cur_zone, cur);
}
