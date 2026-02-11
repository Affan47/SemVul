dbAllocDmapBU(struct bmap * bmp, struct dmap * dp, s64 blkno,
			 int nblocks)
{
	int rc;
	int dbitno, word, rembits, nb, nwords, wbitno, agno;
	s8 oldroot;
	struct dmaptree *tp = (struct dmaptree *) & dp->tree;


	oldroot = tp->stree[ROOT];


	dbitno = blkno & (BPERDMAP - 1);
	word = dbitno >> L2DBWORD;


	assert(dbitno + nblocks <= BPERDMAP);


	for (rembits = nblocks; rembits > 0; rembits -= nb, dbitno += nb) {


		wbitno = dbitno & (DBWORD - 1);
		nb = min(rembits, DBWORD - wbitno);


		if (nb < DBWORD) {


			dp->wmap[word] |= cpu_to_le32(ONES << (DBWORD - nb)
						      >> wbitno);

			word++;
		} else {


			nwords = rembits >> L2DBWORD;
			memset(&dp->wmap[word], (int) ONES, nwords * 4);


			nb = nwords << L2DBWORD;
			word += nwords;
		}
	}


	le32_add_cpu(&dp->nfree, -nblocks);


	dbInitDmapTree(dp);

	BMAP_LOCK(bmp);


	agno = blkno >> bmp->db_agl2size;
	if (agno > bmp->db_maxag)
		bmp->db_maxag = agno;


	bmp->db_agfree[agno] -= nblocks;
	bmp->db_nfree -= nblocks;

	BMAP_UNLOCK(bmp);


	if (tp->stree[ROOT] == oldroot)
		return (0);


	if ((rc = dbAdjCtl(bmp, blkno, tp->stree[ROOT], 1, 0)))
		dbFreeBits(bmp, dp, blkno, nblocks);

	return (rc);
}
