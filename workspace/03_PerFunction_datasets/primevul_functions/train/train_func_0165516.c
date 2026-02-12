static void mpage_add_bh_to_extent(struct mpage_da_data *mpd,
				   sector_t logical, struct buffer_head *bh)
{
	sector_t next;
	size_t b_size = bh->b_size;
	struct buffer_head *lbh = &mpd->lbh;
	int nrblocks = lbh->b_size >> mpd->inode->i_blkbits;


	if (!(EXT4_I(mpd->inode)->i_flags & EXT4_EXTENTS_FL)) {
		if (nrblocks >= EXT4_MAX_TRANS_DATA) {


			goto flush_it;
		} else if ((nrblocks + (b_size >> mpd->inode->i_blkbits)) >
				EXT4_MAX_TRANS_DATA) {


			b_size = (EXT4_MAX_TRANS_DATA - nrblocks) <<
						mpd->inode->i_blkbits;

		}
	}


	if (lbh->b_size == 0) {
		lbh->b_blocknr = logical;
		lbh->b_size = b_size;
		lbh->b_state = bh->b_state & BH_FLAGS;
		return;
	}

	next = lbh->b_blocknr + nrblocks;


	if (logical == next && (bh->b_state & BH_FLAGS) == lbh->b_state) {
		lbh->b_size += b_size;
		return;
	}

flush_it:


	if (mpage_da_map_blocks(mpd) == 0)
		mpage_da_submit_io(mpd);
	mpd->io_done = 1;
	return;
}
