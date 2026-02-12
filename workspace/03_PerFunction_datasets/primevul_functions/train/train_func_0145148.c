xfs_bmap_btalloc(
	struct xfs_bmalloca	*ap)
{
	xfs_mount_t	*mp;
	xfs_alloctype_t	atype = 0;
	xfs_extlen_t	align = 0;
	xfs_agnumber_t	fb_agno;
	xfs_agnumber_t	ag;
	xfs_alloc_arg_t	args;
	xfs_fileoff_t	orig_offset;
	xfs_extlen_t	orig_length;
	xfs_extlen_t	blen;
	xfs_extlen_t	nextminlen = 0;
	int		nullfb;
	int		isaligned;
	int		tryagain;
	int		error;
	int		stripe_align;

	ASSERT(ap->length);
	orig_offset = ap->offset;
	orig_length = ap->length;

	mp = ap->ip->i_mount;


	stripe_align = 0;
	if (mp->m_swidth && (mp->m_flags & XFS_MOUNT_SWALLOC))
		stripe_align = mp->m_swidth;
	else if (mp->m_dalign)
		stripe_align = mp->m_dalign;

	if (ap->flags & XFS_BMAPI_COWFORK)
		align = xfs_get_cowextsz_hint(ap->ip);
	else if (xfs_alloc_is_userdata(ap->datatype))
		align = xfs_get_extsz_hint(ap->ip);
	if (align) {
		error = xfs_bmap_extsize_align(mp, &ap->got, &ap->prev,
						align, 0, ap->eof, 0, ap->conv,
						&ap->offset, &ap->length);
		ASSERT(!error);
		ASSERT(ap->length);
	}


	nullfb = *ap->firstblock == NULLFSBLOCK;
	fb_agno = nullfb ? NULLAGNUMBER : XFS_FSB_TO_AGNO(mp, *ap->firstblock);
	if (nullfb) {
		if (xfs_alloc_is_userdata(ap->datatype) &&
		    xfs_inode_is_filestream(ap->ip)) {
			ag = xfs_filestream_lookup_ag(ap->ip);
			ag = (ag != NULLAGNUMBER) ? ag : 0;
			ap->blkno = XFS_AGB_TO_FSB(mp, ag, 0);
		} else {
			ap->blkno = XFS_INO_TO_FSB(mp, ap->ip->i_ino);
		}
	} else
		ap->blkno = *ap->firstblock;

	xfs_bmap_adjacent(ap);


	if (nullfb || XFS_FSB_TO_AGNO(mp, ap->blkno) == fb_agno)
		;
	else
		ap->blkno = *ap->firstblock;


	tryagain = isaligned = 0;
	memset(&args, 0, sizeof(args));
	args.tp = ap->tp;
	args.mp = mp;
	args.fsbno = ap->blkno;
	xfs_rmap_skip_owner_update(&args.oinfo);


	args.maxlen = MIN(ap->length, mp->m_ag_max_usable);
	args.firstblock = *ap->firstblock;
	blen = 0;
	if (nullfb) {


		if (xfs_alloc_is_userdata(ap->datatype) &&
		    xfs_inode_is_filestream(ap->ip))
			error = xfs_bmap_btalloc_filestreams(ap, &args, &blen);
		else
			error = xfs_bmap_btalloc_nullfb(ap, &args, &blen);
		if (error)
			return error;
	} else if (ap->dfops->dop_low) {
		if (xfs_inode_is_filestream(ap->ip))
			args.type = XFS_ALLOCTYPE_FIRST_AG;
		else
			args.type = XFS_ALLOCTYPE_START_BNO;
		args.total = args.minlen = ap->minlen;
	} else {
		args.type = XFS_ALLOCTYPE_NEAR_BNO;
		args.total = ap->total;
		args.minlen = ap->minlen;
	}

	if (align) {
		args.prod = align;
		if ((args.mod = (xfs_extlen_t)do_mod(ap->offset, args.prod)))
			args.mod = (xfs_extlen_t)(args.prod - args.mod);
	} else if (mp->m_sb.sb_blocksize >= PAGE_SIZE) {
		args.prod = 1;
		args.mod = 0;
	} else {
		args.prod = PAGE_SIZE >> mp->m_sb.sb_blocklog;
		if ((args.mod = (xfs_extlen_t)(do_mod(ap->offset, args.prod))))
			args.mod = (xfs_extlen_t)(args.prod - args.mod);
	}


	if (!ap->dfops->dop_low && ap->aeof) {
		if (!ap->offset) {
			args.alignment = stripe_align;
			atype = args.type;
			isaligned = 1;


			if (blen > args.alignment && blen <= args.maxlen)
				args.minlen = blen - args.alignment;
			args.minalignslop = 0;
		} else {


			atype = args.type;
			tryagain = 1;
			args.type = XFS_ALLOCTYPE_THIS_BNO;
			args.alignment = 1;


			if (blen > stripe_align && blen <= args.maxlen)
				nextminlen = blen - stripe_align;
			else
				nextminlen = args.minlen;
			if (nextminlen + stripe_align > args.minlen + 1)
				args.minalignslop =
					nextminlen + stripe_align -
					args.minlen - 1;
			else
				args.minalignslop = 0;
		}
	} else {
		args.alignment = 1;
		args.minalignslop = 0;
	}
	args.minleft = ap->minleft;
	args.wasdel = ap->wasdel;
	args.resv = XFS_AG_RESV_NONE;
	args.datatype = ap->datatype;
	if (ap->datatype & XFS_ALLOC_USERDATA_ZERO)
		args.ip = ap->ip;

	error = xfs_alloc_vextent(&args);
	if (error)
		return error;

	if (tryagain && args.fsbno == NULLFSBLOCK) {


		args.type = atype;
		args.fsbno = ap->blkno;
		args.alignment = stripe_align;
		args.minlen = nextminlen;
		args.minalignslop = 0;
		isaligned = 1;
		if ((error = xfs_alloc_vextent(&args)))
			return error;
	}
	if (isaligned && args.fsbno == NULLFSBLOCK) {


		args.type = atype;
		args.fsbno = ap->blkno;
		args.alignment = 0;
		if ((error = xfs_alloc_vextent(&args)))
			return error;
	}
	if (args.fsbno == NULLFSBLOCK && nullfb &&
	    args.minlen > ap->minlen) {
		args.minlen = ap->minlen;
		args.type = XFS_ALLOCTYPE_START_BNO;
		args.fsbno = ap->blkno;
		if ((error = xfs_alloc_vextent(&args)))
			return error;
	}
	if (args.fsbno == NULLFSBLOCK && nullfb) {
		args.fsbno = 0;
		args.type = XFS_ALLOCTYPE_FIRST_AG;
		args.total = ap->minlen;
		if ((error = xfs_alloc_vextent(&args)))
			return error;
		ap->dfops->dop_low = true;
	}
	if (args.fsbno != NULLFSBLOCK) {


		ASSERT(*ap->firstblock == NULLFSBLOCK ||
		       XFS_FSB_TO_AGNO(mp, *ap->firstblock) <=
		       XFS_FSB_TO_AGNO(mp, args.fsbno));

		ap->blkno = args.fsbno;
		if (*ap->firstblock == NULLFSBLOCK)
			*ap->firstblock = args.fsbno;
		ASSERT(nullfb || fb_agno <= args.agno);
		ap->length = args.len;


		if (ap->length <= orig_length)
			ap->offset = orig_offset;
		else if (ap->offset + ap->length < orig_offset + orig_length)
			ap->offset = orig_offset + orig_length - ap->length;
		xfs_bmap_btalloc_accounting(ap, &args);
	} else {
		ap->blkno = NULLFSBLOCK;
		ap->length = 0;
	}
	return 0;
}
