static int ext4_da_writepages(struct address_space *mapping,
			      struct writeback_control *wbc)
{
	pgoff_t	index;
	int range_whole = 0;
	handle_t *handle = NULL;
	struct mpage_da_data mpd;
	struct inode *inode = mapping->host;
	int no_nrwrite_index_update;
	int pages_written = 0;
	long pages_skipped;
	int needed_blocks, ret = 0, nr_to_writebump = 0;
	struct ext4_sb_info *sbi = EXT4_SB(mapping->host->i_sb);

	trace_mark(ext4_da_writepages,
		   "dev %s ino %lu nr_t_write %ld "
		   "pages_skipped %ld range_start %llu "
		   "range_end %llu nonblocking %d "
		   "for_kupdate %d for_reclaim %d "
		   "for_writepages %d range_cyclic %d",
		   inode->i_sb->s_id, inode->i_ino,
		   wbc->nr_to_write, wbc->pages_skipped,
		   (unsigned long long) wbc->range_start,
		   (unsigned long long) wbc->range_end,
		   wbc->nonblocking, wbc->for_kupdate,
		   wbc->for_reclaim, wbc->for_writepages,
		   wbc->range_cyclic);


	if (!mapping->nrpages || !mapping_tagged(mapping, PAGECACHE_TAG_DIRTY))
		return 0;


	if (unlikely(sbi->s_mount_opt & EXT4_MOUNT_ABORT))
		return -EROFS;


	if (wbc->nr_to_write < sbi->s_mb_stream_request) {
		nr_to_writebump = sbi->s_mb_stream_request - wbc->nr_to_write;
		wbc->nr_to_write = sbi->s_mb_stream_request;
	}
	if (wbc->range_start == 0 && wbc->range_end == LLONG_MAX)
		range_whole = 1;

	if (wbc->range_cyclic)
		index = mapping->writeback_index;
	else
		index = wbc->range_start >> PAGE_CACHE_SHIFT;

	mpd.wbc = wbc;
	mpd.inode = mapping->host;


	no_nrwrite_index_update = wbc->no_nrwrite_index_update;
	wbc->no_nrwrite_index_update = 1;
	pages_skipped = wbc->pages_skipped;

	while (!ret && wbc->nr_to_write > 0) {


		BUG_ON(ext4_should_journal_data(inode));
		needed_blocks = ext4_da_writepages_trans_blocks(inode);


		handle = ext4_journal_start(inode, needed_blocks);
		if (IS_ERR(handle)) {
			ret = PTR_ERR(handle);
			printk(KERN_CRIT "%s: jbd2_start: "
			       "%ld pages, ino %lu; err %d\n", __func__,
				wbc->nr_to_write, inode->i_ino, ret);
			dump_stack();
			goto out_writepages;
		}
		mpd.get_block = ext4_da_get_block_write;
		ret = mpage_da_writepages(mapping, wbc, &mpd);

		ext4_journal_stop(handle);

		if (mpd.retval == -ENOSPC) {


			jbd2_journal_force_commit_nested(sbi->s_journal);
			wbc->pages_skipped = pages_skipped;
			ret = 0;
		} else if (ret == MPAGE_DA_EXTENT_TAIL) {


			pages_written += mpd.pages_written;
			wbc->pages_skipped = pages_skipped;
			ret = 0;
		} else if (wbc->nr_to_write)


			break;
	}
	if (pages_skipped != wbc->pages_skipped)
		printk(KERN_EMERG "This should not happen leaving %s "
				"with nr_to_write = %ld ret = %d\n",
				__func__, wbc->nr_to_write, ret);


	index += pages_written;
	if (wbc->range_cyclic || (range_whole && wbc->nr_to_write > 0))


		mapping->writeback_index = index;

out_writepages:
	if (!no_nrwrite_index_update)
		wbc->no_nrwrite_index_update = 0;
	wbc->nr_to_write -= nr_to_writebump;
	trace_mark(ext4_da_writepage_result,
		   "dev %s ino %lu ret %d pages_written %d "
		   "pages_skipped %ld congestion %d "
		   "more_io %d no_nrwrite_index_update %d",
		   inode->i_sb->s_id, inode->i_ino, ret,
		   pages_written, wbc->pages_skipped,
		   wbc->encountered_congestion, wbc->more_io,
		   wbc->no_nrwrite_index_update);
	return ret;
}
