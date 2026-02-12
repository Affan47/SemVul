static int alloc_and_dissolve_huge_page(struct hstate *h, struct page *old_page,
					struct list_head *list)
{
	gfp_t gfp_mask = htlb_alloc_mask(h) | __GFP_THISNODE;
	int nid = page_to_nid(old_page);
	bool alloc_retry = false;
	struct page *new_page;
	int ret = 0;


alloc_retry:
	new_page = alloc_buddy_huge_page(h, gfp_mask, nid, NULL, NULL);
	if (!new_page)
		return -ENOMEM;


	SetHPageTemporary(new_page);
	if (!put_page_testzero(new_page)) {
		if (alloc_retry)
			return -EBUSY;

		alloc_retry = true;
		goto alloc_retry;
	}
	ClearHPageTemporary(new_page);

	__prep_new_huge_page(h, new_page);

retry:
	spin_lock_irq(&hugetlb_lock);
	if (!PageHuge(old_page)) {


		goto free_new;
	} else if (page_count(old_page)) {


		spin_unlock_irq(&hugetlb_lock);
		if (!isolate_huge_page(old_page, list))
			ret = -EBUSY;
		spin_lock_irq(&hugetlb_lock);
		goto free_new;
	} else if (!HPageFreed(old_page)) {


		spin_unlock_irq(&hugetlb_lock);
		cond_resched();
		goto retry;
	} else {


		remove_hugetlb_page(h, old_page, false);


		__prep_account_new_huge_page(h, nid);
		enqueue_huge_page(h, new_page);


		spin_unlock_irq(&hugetlb_lock);
		update_and_free_page(h, old_page, false);
	}

	return ret;

free_new:
	spin_unlock_irq(&hugetlb_lock);

	set_page_refcounted(new_page);
	update_and_free_page(h, new_page, false);

	return ret;
}
