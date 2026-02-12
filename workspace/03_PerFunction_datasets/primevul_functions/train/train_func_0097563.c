void free_huge_page(struct page *page)
{


	struct hstate *h = page_hstate(page);
	int nid = page_to_nid(page);
	struct hugepage_subpool *spool = hugetlb_page_subpool(page);
	bool restore_reserve;
	unsigned long flags;

	VM_BUG_ON_PAGE(page_count(page), page);
	VM_BUG_ON_PAGE(page_mapcount(page), page);

	hugetlb_set_page_subpool(page, NULL);
	page->mapping = NULL;
	restore_reserve = HPageRestoreReserve(page);
	ClearHPageRestoreReserve(page);


	if (!restore_reserve) {


		if (hugepage_subpool_put_pages(spool, 1) == 0)
			restore_reserve = true;
	}

	spin_lock_irqsave(&hugetlb_lock, flags);
	ClearHPageMigratable(page);
	hugetlb_cgroup_uncharge_page(hstate_index(h),
				     pages_per_huge_page(h), page);
	hugetlb_cgroup_uncharge_page_rsvd(hstate_index(h),
					  pages_per_huge_page(h), page);
	if (restore_reserve)
		h->resv_huge_pages++;

	if (HPageTemporary(page)) {
		remove_hugetlb_page(h, page, false);
		spin_unlock_irqrestore(&hugetlb_lock, flags);
		update_and_free_page(h, page, true);
	} else if (h->surplus_huge_pages_node[nid]) {

		remove_hugetlb_page(h, page, true);
		spin_unlock_irqrestore(&hugetlb_lock, flags);
		update_and_free_page(h, page, true);
	} else {
		arch_clear_hugepage_flags(page);
		enqueue_huge_page(h, page);
		spin_unlock_irqrestore(&hugetlb_lock, flags);
	}
}
