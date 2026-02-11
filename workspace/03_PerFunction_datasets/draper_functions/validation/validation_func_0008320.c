bmap_extent(struct inode *inode, uint32_t block, size_t *nblocks)
{
    struct fs_info *fs = inode->fs;
    const struct ext4_extent_header *leaf;
    const struct ext4_extent *ext;
    int i;
    block_t start;

    leaf = ext4_find_leaf(fs, &PVT(inode)->i_extent_hdr, block);
    if (!leaf) {
	printf("ERROR, extent leaf not found\n");
	return 0;
    }

    ext = EXT4_FIRST_EXTENT(leaf);
    for (i = 0; i < leaf->eh_entries; i++) {
	if (block < ext[i].ee_block)
	    break;
    }
    if (--i < 0) {
	printf("ERROR, not find the right block\n");
	return 0;
    }


    block -= ext[i].ee_block;
    if (block >= ext[i].ee_len)
	return 0;
    start = ((block_t)ext[i].ee_start_hi << 32) + ext[i].ee_start_lo;

    if (nblocks)
	*nblocks = ext[i].ee_len - block;

    return start + block;
}
