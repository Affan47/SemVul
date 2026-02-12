xfs_alloc_longest_free_extent(
	struct xfs_perag	*pag,
	xfs_extlen_t		need,
	xfs_extlen_t		reserved)
{
	xfs_extlen_t		delta = 0;


	if (need > pag->pagf_flcount)
		delta = need - pag->pagf_flcount;


	if (pag->pagf_freeblks - pag->pagf_longest < reserved)
		delta += reserved - (pag->pagf_freeblks - pag->pagf_longest);


	if (pag->pagf_longest > delta)
		return min_t(xfs_extlen_t, pag->pag_mount->m_ag_max_usable,
				pag->pagf_longest - delta);


	return pag->pagf_flcount > 0 || pag->pagf_longest > 0;
}
