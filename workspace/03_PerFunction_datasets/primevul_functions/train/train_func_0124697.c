xfs_alloc_ag_vextent_near(
	struct xfs_alloc_arg	*args)
{
	struct xfs_alloc_cur	acur = {};
	int			error;
	int			i;
	xfs_agblock_t		bno;
	xfs_extlen_t		len;


	if (!args->min_agbno && !args->max_agbno)
		args->max_agbno = args->mp->m_sb.sb_agblocks - 1;
	ASSERT(args->min_agbno <= args->max_agbno);


	if (args->agbno < args->min_agbno)
		args->agbno = args->min_agbno;
	if (args->agbno > args->max_agbno)
		args->agbno = args->max_agbno;

restart:
	len = 0;


	error = xfs_alloc_cur_setup(args, &acur);
	if (error == -ENOSPC) {
		error = xfs_alloc_ag_vextent_small(args, acur.cnt, &bno,
				&len, &i);
		if (error)
			goto out;
		if (i == 0 || len == 0) {
			trace_xfs_alloc_near_noentry(args);
			goto out;
		}
		ASSERT(i == 1);
	} else if (error) {
		goto out;
	}


	if (xfs_btree_islastblock(acur.cnt, 0)) {
		bool		allocated = false;

		error = xfs_alloc_ag_vextent_lastblock(args, &acur, &bno, &len,
				&allocated);
		if (error)
			goto out;
		if (allocated)
			goto alloc_finish;
	}


	error = xfs_alloc_ag_vextent_locality(args, &acur, &i);
	if (error)
		goto out;


	if (!acur.len) {
		if (acur.busy) {
			trace_xfs_alloc_near_busy(args);
			xfs_extent_busy_flush(args->mp, args->pag,
					      acur.busy_gen);
			goto restart;
		}
		trace_xfs_alloc_size_neither(args);
		args->agbno = NULLAGBLOCK;
		goto out;
	}

alloc_finish:

	error = xfs_alloc_cur_finish(args, &acur);

out:
	xfs_alloc_cur_close(&acur, error);
	return error;
}
