static int __mpage_da_writepage(struct page *page,
				struct writeback_control *wbc, void *data)
{
	struct mpage_da_data *mpd = data;
	struct inode *inode = mpd->inode;
	struct buffer_head *bh, *head, fake;
	sector_t logical;

	if (mpd->io_done) {


		redirty_page_for_writepage(wbc, page);
		unlock_page(page);
		return MPAGE_DA_EXTENT_TAIL;
	}


	if (mpd->next_page != page->index) {


		if (mpd->next_page != mpd->first_page) {
			if (mpage_da_map_blocks(mpd) == 0)
				mpage_da_submit_io(mpd);


			mpd->io_done = 1;
			redirty_page_for_writepage(wbc, page);
			unlock_page(page);
			return MPAGE_DA_EXTENT_TAIL;
		}


		mpd->first_page = page->index;


		mpd->lbh.b_size = 0;
		mpd->lbh.b_state = 0;
		mpd->lbh.b_blocknr = 0;
	}

	mpd->next_page = page->index + 1;
	logical = (sector_t) page->index <<
		  (PAGE_CACHE_SHIFT - inode->i_blkbits);

	if (!page_has_buffers(page)) {


		bh = &fake;
		bh->b_size = PAGE_CACHE_SIZE;
		bh->b_state = 0;
		set_buffer_dirty(bh);
		set_buffer_uptodate(bh);
		mpage_add_bh_to_extent(mpd, logical, bh);
		if (mpd->io_done)
			return MPAGE_DA_EXTENT_TAIL;
	} else {


		head = page_buffers(page);
		bh = head;
		do {
			BUG_ON(buffer_locked(bh));


			if (buffer_dirty(bh) &&
				(!buffer_mapped(bh) || buffer_delay(bh))) {
				mpage_add_bh_to_extent(mpd, logical, bh);
				if (mpd->io_done)
					return MPAGE_DA_EXTENT_TAIL;
			} else if (buffer_dirty(bh) && (buffer_mapped(bh))) {


				if (mpd->lbh.b_size == 0)
					mpd->lbh.b_state =
						bh->b_state & BH_FLAGS;
			}
			logical++;
		} while ((bh = bh->b_this_page) != head);
	}

	return 0;
}
