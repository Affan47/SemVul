xfs_alloc_compute_aligned(
	xfs_alloc_arg_t	*args,
	xfs_agblock_t	foundbno,
	xfs_extlen_t	foundlen,
	xfs_agblock_t	*resbno,
	xfs_extlen_t	*reslen,
	unsigned	*busy_gen)
{
	xfs_agblock_t	bno = foundbno;
	xfs_extlen_t	len = foundlen;
	xfs_extlen_t	diff;
	bool		busy;


	busy = xfs_extent_busy_trim(args, &bno, &len, busy_gen);


	if (bno < args->min_agbno && bno + len > args->min_agbno) {
		diff = args->min_agbno - bno;
		if (len > diff) {
			bno += diff;
			len -= diff;
		}
	}

	if (args->alignment > 1 && len >= args->minlen) {
		xfs_agblock_t	aligned_bno = roundup(bno, args->alignment);

		diff = aligned_bno - bno;

		*resbno = aligned_bno;
		*reslen = diff >= len ? 0 : len - diff;
	} else {
		*resbno = bno;
		*reslen = len;
	}

	return busy;
}
