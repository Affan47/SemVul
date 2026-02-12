__must_hold(&hugetlb_lock)
{
	struct list_head surplus_list;
	struct page *page, *tmp;
	int ret;
	long i;
	long needed, allocated;
	bool alloc_ok = true;

	lockdep_assert_held(&hugetlb_lock);
	needed = (h->resv_huge_pages + delta) - h->free_huge_pages;
	if (needed <= 0) {
		h->resv_huge_pages += delta;
		return 0;
	}

	allocated = 0;
	INIT_LIST_HEAD(&surplus_list);

	ret = -ENOMEM;
retry:
	spin_unlock_irq(&hugetlb_lock);
	for (i = 0; i < needed; i++) {
		page = alloc_surplus_huge_page(h, htlb_alloc_mask(h),
				NUMA_NO_NODE, NULL, true);
		if (!page) {
			alloc_ok = false;
			break;
		}
		list_add(&page->lru, &surplus_list);
		cond_resched();
	}
	allocated += i;


	spin_lock_irq(&hugetlb_lock);
	needed = (h->resv_huge_pages + delta) -
			(h->free_huge_pages + allocated);
	if (needed > 0) {
		if (alloc_ok)
			goto retry;


		goto free;
	}


	needed += allocated;
	h->resv_huge_pages += delta;
	ret = 0;


	list_for_each_entry_safe(page, tmp, &surplus_list, lru) {
		if ((--needed) < 0)
			break;

		enqueue_huge_page(h, page);
	}
free:
	spin_unlock_irq(&hugetlb_lock);


	list_for_each_entry_safe(page, tmp, &surplus_list, lru)
		free_huge_page(page);
	spin_lock_irq(&hugetlb_lock);

	return ret;
}
