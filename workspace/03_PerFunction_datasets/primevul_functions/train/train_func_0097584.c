static void __remove_hugetlb_page(struct hstate *h, struct page *page,
							bool adjust_surplus,
							bool demote)
{
	int nid = page_to_nid(page);

	VM_BUG_ON_PAGE(hugetlb_cgroup_from_page(page), page);
	VM_BUG_ON_PAGE(hugetlb_cgroup_from_page_rsvd(page), page);

	lockdep_assert_held(&hugetlb_lock);
	if (hstate_is_gigantic(h) && !gigantic_page_runtime_supported())
		return;

	list_del(&page->lru);

	if (HPageFreed(page)) {
		h->free_huge_pages--;
		h->free_huge_pages_node[nid]--;
	}
	if (adjust_surplus) {
		h->surplus_huge_pages--;
		h->surplus_huge_pages_node[nid]--;
	}


	if (!demote)
		set_page_refcounted(page);
	if (hstate_is_gigantic(h))
		set_compound_page_dtor(page, NULL_COMPOUND_DTOR);
	else
		set_compound_page_dtor(page, COMPOUND_PAGE_DTOR);

	h->nr_huge_pages--;
	h->nr_huge_pages_node[nid]--;
}
