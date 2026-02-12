xfs_bmap_extsize_align(
	xfs_mount_t	*mp,
	xfs_bmbt_irec_t	*gotp,
	xfs_bmbt_irec_t	*prevp,
	xfs_extlen_t	extsz,
	int		rt,
	int		eof,
	int		delay,
	int		convert,
	xfs_fileoff_t	*offp,
	xfs_extlen_t	*lenp)
{
	xfs_fileoff_t	orig_off;
	xfs_extlen_t	orig_alen;
	xfs_fileoff_t	orig_end;
	xfs_fileoff_t	nexto;
	xfs_fileoff_t	prevo;
	xfs_fileoff_t	align_off;
	xfs_extlen_t	align_alen;
	xfs_extlen_t	temp;

	if (convert)
		return 0;

	orig_off = align_off = *offp;
	orig_alen = align_alen = *lenp;
	orig_end = orig_off + orig_alen;


	if (!delay && !eof &&
	    (orig_off >= gotp->br_startoff) &&
	    (orig_end <= gotp->br_startoff + gotp->br_blockcount)) {
		return 0;
	}


	temp = do_mod(orig_off, extsz);
	if (temp) {
		align_alen += temp;
		align_off -= temp;
	}


	temp = (align_alen % extsz);
	if (temp)
		align_alen += extsz - temp;


	while (align_alen > MAXEXTLEN)
		align_alen -= extsz;
	ASSERT(align_alen <= MAXEXTLEN);


	if (prevp->br_startoff != NULLFILEOFF) {
		if (prevp->br_startblock == HOLESTARTBLOCK)
			prevo = prevp->br_startoff;
		else
			prevo = prevp->br_startoff + prevp->br_blockcount;
	} else
		prevo = 0;
	if (align_off != orig_off && align_off < prevo)
		align_off = prevo;


	if (!eof && gotp->br_startoff != NULLFILEOFF) {
		if ((delay && gotp->br_startblock == HOLESTARTBLOCK) ||
		    (!delay && gotp->br_startblock == DELAYSTARTBLOCK))
			nexto = gotp->br_startoff + gotp->br_blockcount;
		else
			nexto = gotp->br_startoff;
	} else
		nexto = NULLFILEOFF;
	if (!eof &&
	    align_off + align_alen != orig_end &&
	    align_off + align_alen > nexto)
		align_off = nexto > align_alen ? nexto - align_alen : 0;


	if (align_off != orig_off && align_off < prevo)
		align_off = prevo;
	if (align_off + align_alen != orig_end &&
	    align_off + align_alen > nexto &&
	    nexto != NULLFILEOFF) {
		ASSERT(nexto > prevo);
		align_alen = nexto - align_off;
	}


	if (rt && (temp = (align_alen % mp->m_sb.sb_rextsize))) {


		if (orig_off < align_off ||
		    orig_end > align_off + align_alen ||
		    align_alen - temp < orig_alen)
			return -EINVAL;


		if (align_off + temp <= orig_off) {
			align_alen -= temp;
			align_off += temp;
		}


		else if (align_off + align_alen - temp >= orig_end)
			align_alen -= temp;


		else {
			align_alen -= orig_off - align_off;
			align_off = orig_off;
			align_alen -= align_alen % mp->m_sb.sb_rextsize;
		}


		if (orig_off < align_off || orig_end > align_off + align_alen)
			return -EINVAL;
	} else {
		ASSERT(orig_off >= align_off);

		ASSERT(orig_end <= align_off + align_alen ||
		       align_alen + extsz > MAXEXTLEN);
	}

#ifdef DEBUG
	if (!eof && gotp->br_startoff != NULLFILEOFF)
		ASSERT(align_off + align_alen <= gotp->br_startoff);
	if (prevp->br_startoff != NULLFILEOFF)
		ASSERT(align_off >= prevp->br_startoff + prevp->br_blockcount);
#endif

	*lenp = align_alen;
	*offp = align_off;
	return 0;
}
