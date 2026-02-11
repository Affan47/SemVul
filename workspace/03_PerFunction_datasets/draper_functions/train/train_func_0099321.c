dbAllocDmapLev(struct bmap * bmp,
	       struct dmap * dp, int nblocks, int l2nb, s64 * results)
{
	s64 blkno;
	int leafidx, rc;


	assert(l2nb <= L2BPERDMAP);


	if (dbFindLeaf((dmtree_t *) & dp->tree, l2nb, &leafidx))
		return -ENOSPC;


	blkno = le64_to_cpu(dp->start) + (leafidx << L2DBWORD);


	if (dp->tree.stree[leafidx + LEAFIND] < BUDMIN)
		blkno += dbFindBits(le32_to_cpu(dp->wmap[leafidx]), l2nb);


	if ((rc = dbAllocDmap(bmp, dp, blkno, nblocks)) == 0)
		*results = blkno;

	return (rc);
}
