static int demote_free_huge_page(struct hstate *h, struct page *page)
{
	int i, nid = page_to_nid(page);
	struct hstate *target_hstate;
	int rc = 0;

	target_hstate = size_to_hstate(PAGE_SIZE << h->demote_order);

	remove_hugetlb_page_for_demote(h, page, false);
	spin_unlock_irq(&hugetlb_lock);

	rc = alloc_huge_page_vmemmap(h, page);
	if (rc) {

		spin_lock_irq(&hugetlb_lock);
		set_page_refcounted(page);
		add_hugetlb_page(h, page, false);
		return rc;
	}


	destroy_compound_hugetlb_page_for_demote(page, huge_page_order(h));


	mutex_lock(&target_hstate->resize_lock);
	for (i = 0; i < pages_per_huge_page(h);
				i += pages_per_huge_page(target_hstate)) {
		if (hstate_is_gigantic(target_hstate))
			prep_compound_gigantic_page_for_demote(page + i,
							target_hstate->order);
		else
			prep_compound_page(page + i, target_hstate->order);
		set_page_private(page + i, 0);
		set_page_refcounted(page + i);
		prep_new_huge_page(target_hstate, page + i, nid);
		put_page(page + i);
	}
	mutex_unlock(&target_hstate->resize_lock);

	spin_lock_irq(&hugetlb_lock);


	h->max_huge_pages--;
	target_hstate->max_huge_pages += pages_per_huge_page(h);

	return rc;
}
