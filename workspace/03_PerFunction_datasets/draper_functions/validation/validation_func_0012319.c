__xfs_inobt_can_merge(
	struct xfs_inobt_rec_incore	*trec,
	struct xfs_inobt_rec_incore	*srec)
{
	uint64_t			talloc;
	uint64_t			salloc;


	if (trec->ir_startino != srec->ir_startino)
		return false;


	if (!xfs_inobt_issparse(trec->ir_holemask) ||
	    !xfs_inobt_issparse(srec->ir_holemask))
		return false;


	if (!trec->ir_count || !srec->ir_count)
		return false;


	if (trec->ir_count + srec->ir_count > XFS_INODES_PER_CHUNK)
		return false;


	talloc = xfs_inobt_irec_to_allocmask(trec);
	salloc = xfs_inobt_irec_to_allocmask(srec);
	if (talloc & salloc)
		return false;

	return true;
}
