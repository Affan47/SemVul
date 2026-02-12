xfs_alloc_fix_freelist(
	struct xfs_alloc_arg	*args,
	int			flags)
{
	struct xfs_mount	*mp = args->mp;
	struct xfs_perag	*pag = args->pag;
	struct xfs_trans	*tp = args->tp;
	struct xfs_buf		*agbp = NULL;
	struct xfs_buf		*agflbp = NULL;
	struct xfs_alloc_arg	targs;
	xfs_agblock_t		bno;
	xfs_extlen_t		need;
	int			error = 0;


	ASSERT(tp->t_flags & XFS_TRANS_PERM_LOG_RES);

	if (!pag->pagf_init) {
		error = xfs_alloc_read_agf(mp, tp, args->agno, flags, &agbp);
		if (error) {

			if (error == -EAGAIN)
				error = 0;
			goto out_no_agbp;
		}
	}


	if (pag->pagf_metadata && (args->datatype & XFS_ALLOC_USERDATA) &&
	    (flags & XFS_ALLOC_FLAG_TRYLOCK)) {
		ASSERT(!(flags & XFS_ALLOC_FLAG_FREEING));
		goto out_agbp_relse;
	}

	need = xfs_alloc_min_freelist(mp, pag);
	if (!xfs_alloc_space_available(args, need, flags |
			XFS_ALLOC_FLAG_CHECK))
		goto out_agbp_relse;


	if (!agbp) {
		error = xfs_alloc_read_agf(mp, tp, args->agno, flags, &agbp);
		if (error) {

			if (error == -EAGAIN)
				error = 0;
			goto out_no_agbp;
		}
	}


	if (pag->pagf_agflreset)
		xfs_agfl_reset(tp, agbp, pag);


	need = xfs_alloc_min_freelist(mp, pag);
	if (!xfs_alloc_space_available(args, need, flags))
		goto out_agbp_relse;


	memset(&targs, 0, sizeof(targs));

	if (flags & XFS_ALLOC_FLAG_NORMAP)
		targs.oinfo = XFS_RMAP_OINFO_SKIP_UPDATE;
	else
		targs.oinfo = XFS_RMAP_OINFO_AG;
	while (!(flags & XFS_ALLOC_FLAG_NOSHRINK) && pag->pagf_flcount > need) {
		error = xfs_alloc_get_freelist(tp, agbp, &bno, 0);
		if (error)
			goto out_agbp_relse;


		xfs_defer_agfl_block(tp, args->agno, bno, &targs.oinfo);
	}

	targs.tp = tp;
	targs.mp = mp;
	targs.agbp = agbp;
	targs.agno = args->agno;
	targs.alignment = targs.minlen = targs.prod = 1;
	targs.type = XFS_ALLOCTYPE_THIS_AG;
	targs.pag = pag;
	error = xfs_alloc_read_agfl(mp, tp, targs.agno, &agflbp);
	if (error)
		goto out_agbp_relse;


	while (pag->pagf_flcount < need) {
		targs.agbno = 0;
		targs.maxlen = need - pag->pagf_flcount;
		targs.resv = XFS_AG_RESV_AGFL;


		error = xfs_alloc_ag_vextent(&targs);
		if (error)
			goto out_agflbp_relse;


		if (targs.agbno == NULLAGBLOCK) {
			if (flags & XFS_ALLOC_FLAG_FREEING)
				break;
			goto out_agflbp_relse;
		}


		for (bno = targs.agbno; bno < targs.agbno + targs.len; bno++) {
			error = xfs_alloc_put_freelist(tp, agbp,
							agflbp, bno, 0);
			if (error)
				goto out_agflbp_relse;
		}
	}
	xfs_trans_brelse(tp, agflbp);
	args->agbp = agbp;
	return 0;

out_agflbp_relse:
	xfs_trans_brelse(tp, agflbp);
out_agbp_relse:
	if (agbp)
		xfs_trans_brelse(tp, agbp);
out_no_agbp:
	args->agbp = NULL;
	return error;
}
