xfs_bmap_select_minlen(
	struct xfs_bmalloca	*ap,
	struct xfs_alloc_arg	*args,
	xfs_extlen_t		*blen,
	int			notinit)
{
	if (notinit || *blen < ap->minlen) {


		args->minlen = ap->minlen;
	} else if (*blen < args->maxlen) {


		args->minlen = *blen;
	} else {


		args->minlen = args->maxlen;
	}
}
