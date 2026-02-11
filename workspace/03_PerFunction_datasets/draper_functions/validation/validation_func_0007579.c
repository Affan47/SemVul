pageout(struct page *page, struct address_space *mapping,
			 struct scan_control *sc)
{


	if (!is_page_cache_freeable(page))
		return PAGE_KEEP;
	if (!mapping) {


		if (page_has_private(page)) {
			if (try_to_free_buffers(page)) {
				ClearPageDirty(page);
				pr_info("%s: orphaned page\n", __func__);
				return PAGE_CLEAN;
			}
		}
		return PAGE_KEEP;
	}
	if (mapping->a_ops->writepage == NULL)
		return PAGE_ACTIVATE;
	if (!may_write_to_inode(mapping->host, sc))
		return PAGE_KEEP;

	if (clear_page_dirty_for_io(page)) {
		int res;
		struct writeback_control wbc = {
			.sync_mode = WB_SYNC_NONE,
			.nr_to_write = SWAP_CLUSTER_MAX,
			.range_start = 0,
			.range_end = LLONG_MAX,
			.for_reclaim = 1,
		};

		SetPageReclaim(page);
		res = mapping->a_ops->writepage(page, &wbc);
		if (res < 0)
			handle_write_error(mapping, page, res);
		if (res == AOP_WRITEPAGE_ACTIVATE) {
			ClearPageReclaim(page);
			return PAGE_ACTIVATE;
		}

		if (!PageWriteback(page)) {

			ClearPageReclaim(page);
		}
		trace_mm_vmscan_writepage(page, trace_reclaim_flags(page));
		inc_zone_page_state(page, NR_VMSCAN_WRITE);
		return PAGE_SUCCESS;
	}

	return PAGE_CLEAN;
}
