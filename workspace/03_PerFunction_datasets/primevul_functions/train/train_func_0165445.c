static int ext4_get_blocks_handle(handle_t *handle, struct inode *inode,
				  ext4_lblk_t iblock, unsigned int maxblocks,
				  struct buffer_head *bh_result,
				  int create, int extend_disksize)
{
	int err = -EIO;
	ext4_lblk_t offsets[4];
	Indirect chain[4];
	Indirect *partial;
	ext4_fsblk_t goal;
	int indirect_blks;
	int blocks_to_boundary = 0;
	int depth;
	struct ext4_inode_info *ei = EXT4_I(inode);
	int count = 0;
	ext4_fsblk_t first_block = 0;
	loff_t disksize;


	J_ASSERT(!(EXT4_I(inode)->i_flags & EXT4_EXTENTS_FL));
	J_ASSERT(handle != NULL || create == 0);
	depth = ext4_block_to_path(inode, iblock, offsets,
					&blocks_to_boundary);

	if (depth == 0)
		goto out;

	partial = ext4_get_branch(inode, depth, offsets, chain, &err);


	if (!partial) {
		first_block = le32_to_cpu(chain[depth - 1].key);
		clear_buffer_new(bh_result);
		count++;

		while (count < maxblocks && count <= blocks_to_boundary) {
			ext4_fsblk_t blk;

			blk = le32_to_cpu(*(chain[depth-1].p + count));

			if (blk == first_block + count)
				count++;
			else
				break;
		}
		goto got_it;
	}


	if (!create || err == -EIO)
		goto cleanup;


	goal = ext4_find_goal(inode, iblock, partial);


	indirect_blks = (chain + depth) - partial - 1;


	count = ext4_blks_to_allocate(partial, indirect_blks,
					maxblocks, blocks_to_boundary);


	err = ext4_alloc_branch(handle, inode, iblock, indirect_blks,
					&count, goal,
					offsets + (partial - chain), partial);


	if (!err)
		err = ext4_splice_branch(handle, inode, iblock,
					partial, indirect_blks, count);


	if (!err && extend_disksize) {
		disksize = ((loff_t) iblock + count) << inode->i_blkbits;
		if (disksize > i_size_read(inode))
			disksize = i_size_read(inode);
		if (disksize > ei->i_disksize)
			ei->i_disksize = disksize;
	}
	if (err)
		goto cleanup;

	set_buffer_new(bh_result);
got_it:
	map_bh(bh_result, inode->i_sb, le32_to_cpu(chain[depth-1].key));
	if (count > blocks_to_boundary)
		set_buffer_boundary(bh_result);
	err = count;

	partial = chain + depth - 1;
cleanup:
	while (partial > chain) {
		BUFFER_TRACE(partial->bh, "call brelse");
		brelse(partial->bh);
		partial--;
	}
	BUFFER_TRACE(bh_result, "returned");
out:
	return err;
}
