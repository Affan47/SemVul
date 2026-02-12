static void add_hugetlb_page(struct hstate *h, struct page *page,
			     bool adjust_surplus)
{
	int zeroed;
	int nid = page_to_nid(page);

	VM_BUG_ON_PAGE(!HPageVmemmapOptimized(page), page);

	lockdep_assert_held(&hugetlb_lock);

	INIT_LIST_HEAD(&page->lru);
	h->nr_huge_pages++;
	h->nr_huge_pages_node[nid]++;

	if (adjust_surplus) {
		h->surplus_huge_pages++;
		h->surplus_huge_pages_node[nid]++;
	}

	set_compound_page_dtor(page, HUGETLB_PAGE_DTOR);
	set_page_private(page, 0);
	SetHPageVmemmapOptimized(page);


	zeroed = put_page_testzero(page);
	if (!zeroed)


		return;

	arch_clear_hugepage_flags(page);
	enqueue_huge_page(h, page);
}
