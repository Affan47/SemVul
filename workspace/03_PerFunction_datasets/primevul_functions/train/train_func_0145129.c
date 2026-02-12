xfs_bmap_add_attrfork_extents(
	xfs_trans_t		*tp,
	xfs_inode_t		*ip,
	xfs_fsblock_t		*firstblock,
	struct xfs_defer_ops	*dfops,
	int			*flags)
{
	xfs_btree_cur_t		*cur;
	int			error;

	if (ip->i_d.di_nextents * sizeof(xfs_bmbt_rec_t) <= XFS_IFORK_DSIZE(ip))
		return 0;
	cur = NULL;
	error = xfs_bmap_extents_to_btree(tp, ip, firstblock, dfops, &cur, 0,
		flags, XFS_DATA_FORK);
	if (cur) {
		cur->bc_private.b.allocated = 0;
		xfs_btree_del_cursor(cur,
			error ? XFS_BTREE_ERROR : XFS_BTREE_NOERROR);
	}
	return error;
}
