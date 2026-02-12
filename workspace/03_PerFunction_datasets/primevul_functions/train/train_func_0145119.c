xfs_bmap_add_attrfork_btree(
	xfs_trans_t		*tp,
	xfs_inode_t		*ip,
	xfs_fsblock_t		*firstblock,
	struct xfs_defer_ops	*dfops,
	int			*flags)
{
	xfs_btree_cur_t		*cur;
	int			error;
	xfs_mount_t		*mp;
	int			stat;

	mp = ip->i_mount;
	if (ip->i_df.if_broot_bytes <= XFS_IFORK_DSIZE(ip))
		*flags |= XFS_ILOG_DBROOT;
	else {
		cur = xfs_bmbt_init_cursor(mp, tp, ip, XFS_DATA_FORK);
		cur->bc_private.b.dfops = dfops;
		cur->bc_private.b.firstblock = *firstblock;
		error = xfs_bmbt_lookup_first(cur, &stat);
		if (error)
			goto error0;

		XFS_WANT_CORRUPTED_GOTO(mp, stat == 1, error0);
		if ((error = xfs_btree_new_iroot(cur, flags, &stat)))
			goto error0;
		if (stat == 0) {
			xfs_btree_del_cursor(cur, XFS_BTREE_NOERROR);
			return -ENOSPC;
		}
		*firstblock = cur->bc_private.b.firstblock;
		cur->bc_private.b.allocated = 0;
		xfs_btree_del_cursor(cur, XFS_BTREE_NOERROR);
	}
	return 0;
error0:
	xfs_btree_del_cursor(cur, XFS_BTREE_ERROR);
	return error;
}
