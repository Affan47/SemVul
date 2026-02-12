xfs_attr3_leaf_verify(
	struct xfs_buf			*bp)
{
	struct xfs_attr3_icleaf_hdr	ichdr;
	struct xfs_mount		*mp = bp->b_mount;
	struct xfs_attr_leafblock	*leaf = bp->b_addr;
	struct xfs_attr_leaf_entry	*entries;
	struct xfs_attr_leaf_entry	*ent;
	char				*buf_end;
	uint32_t			end;
	__u32				last_hashval = 0;
	int				i;
	xfs_failaddr_t			fa;

	xfs_attr3_leaf_hdr_from_disk(mp->m_attr_geo, &ichdr, leaf);

	fa = xfs_da3_blkinfo_verify(bp, bp->b_addr);
	if (fa)
		return fa;


	if (ichdr.firstused > mp->m_attr_geo->blksize)
		return __this_address;
	if (ichdr.firstused < xfs_attr3_leaf_hdr_size(leaf))
		return __this_address;


	entries = xfs_attr3_leaf_entryp(bp->b_addr);
	if ((char *)&entries[ichdr.count] >
	    (char *)bp->b_addr + ichdr.firstused)
		return __this_address;


	buf_end = (char *)bp->b_addr + mp->m_attr_geo->blksize;
	for (i = 0, ent = entries; i < ichdr.count; ent++, i++) {
		fa = xfs_attr3_leaf_verify_entry(mp, buf_end, leaf, &ichdr,
				ent, i, &last_hashval);
		if (fa)
			return fa;
	}


	for (i = 0; i < XFS_ATTR_LEAF_MAPSIZE; i++) {
		if (ichdr.freemap[i].base > mp->m_attr_geo->blksize)
			return __this_address;
		if (ichdr.freemap[i].base & 0x3)
			return __this_address;
		if (ichdr.freemap[i].size > mp->m_attr_geo->blksize)
			return __this_address;
		if (ichdr.freemap[i].size & 0x3)
			return __this_address;


		end = (uint32_t)ichdr.freemap[i].base + ichdr.freemap[i].size;
		if (end < ichdr.freemap[i].base)
			return __this_address;
		if (end > mp->m_attr_geo->blksize)
			return __this_address;
	}

	return NULL;
}
