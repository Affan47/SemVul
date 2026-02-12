static void return_unused_surplus_pages(struct hstate *h,
					unsigned long unused_resv_pages)
{
	unsigned long nr_pages;
	struct page *page;
	LIST_HEAD(page_list);

	lockdep_assert_held(&hugetlb_lock);

	h->resv_huge_pages -= unused_resv_pages;


	if (hstate_is_gigantic(h))
		goto out;


	nr_pages = min(unused_resv_pages, h->surplus_huge_pages);


	while (nr_pages--) {
		page = remove_pool_huge_page(h, &node_states[N_MEMORY], 1);
		if (!page)
			goto out;

		list_add(&page->lru, &page_list);
	}

out:
	spin_unlock_irq(&hugetlb_lock);
	update_and_free_pages_bulk(h, &page_list);
	spin_lock_irq(&hugetlb_lock);
}
