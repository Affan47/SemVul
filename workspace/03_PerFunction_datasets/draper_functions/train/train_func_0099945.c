lru_deactivate_file_fn(struct page *page, struct lruvec *lruvec,
			      void *arg)
{
	int lru, file;
	bool active;

	if (!PageLRU(page))
		return;

	if (PageUnevictable(page))
		return;


	if (page_mapped(page))
		return;

	active = PageActive(page);
	file = page_is_file_cache(page);
	lru = page_lru_base_type(page);

	del_page_from_lru_list(page, lruvec, lru + active);
	ClearPageActive(page);
	ClearPageReferenced(page);
	add_page_to_lru_list(page, lruvec, lru);

	if (PageWriteback(page) || PageDirty(page)) {


		SetPageReclaim(page);
	} else {


		list_move_tail(&page->lru, &lruvec->lists[lru]);
		__count_vm_event(PGROTATED);
	}

	if (active)
		__count_vm_event(PGDEACTIVATE);
	update_page_reclaim_stat(lruvec, file, 0);
}
