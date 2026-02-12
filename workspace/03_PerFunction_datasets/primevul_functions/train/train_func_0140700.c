static void __split_huge_page_tail(struct page *head, int tail,
		struct lruvec *lruvec, struct list_head *list)
{
	struct page *page_tail = head + tail;

	VM_BUG_ON_PAGE(atomic_read(&page_tail->_mapcount) != -1, page_tail);
	VM_BUG_ON_PAGE(page_ref_count(page_tail) != 0, page_tail);


	if (PageAnon(head) && !PageSwapCache(head)) {
		page_ref_inc(page_tail);
	} else {

		page_ref_add(page_tail, 2);
	}

	page_tail->flags &= ~PAGE_FLAGS_CHECK_AT_PREP;
	page_tail->flags |= (head->flags &
			((1L << PG_referenced) |
			 (1L << PG_swapbacked) |
			 (1L << PG_swapcache) |
			 (1L << PG_mlocked) |
			 (1L << PG_uptodate) |
			 (1L << PG_active) |
			 (1L << PG_locked) |
			 (1L << PG_unevictable) |
			 (1L << PG_dirty)));


	smp_wmb();

	clear_compound_head(page_tail);

	if (page_is_young(head))
		set_page_young(page_tail);
	if (page_is_idle(head))
		set_page_idle(page_tail);


	VM_BUG_ON_PAGE(tail > 2 && page_tail->mapping != TAIL_MAPPING,
			page_tail);
	page_tail->mapping = head->mapping;

	page_tail->index = head->index + tail;
	page_cpupid_xchg_last(page_tail, page_cpupid_last(head));
	lru_add_page_tail(head, page_tail, lruvec, list);
}
