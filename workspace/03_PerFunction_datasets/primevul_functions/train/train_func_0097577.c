int dissolve_free_huge_page(struct page *page)
{
	int rc = -EBUSY;

retry:

	if (!PageHuge(page))
		return 0;

	spin_lock_irq(&hugetlb_lock);
	if (!PageHuge(page)) {
		rc = 0;
		goto out;
	}

	if (!page_count(page)) {
		struct page *head = compound_head(page);
		struct hstate *h = page_hstate(head);
		if (h->free_huge_pages - h->resv_huge_pages == 0)
			goto out;


		if (unlikely(!HPageFreed(head))) {
			spin_unlock_irq(&hugetlb_lock);
			cond_resched();


			goto retry;
		}

		remove_hugetlb_page(h, head, false);
		h->max_huge_pages--;
		spin_unlock_irq(&hugetlb_lock);


		rc = alloc_huge_page_vmemmap(h, head);
		if (!rc) {


			if (PageHWPoison(head) && page != head) {
				SetPageHWPoison(page);
				ClearPageHWPoison(head);
			}
			update_and_free_page(h, head, false);
		} else {
			spin_lock_irq(&hugetlb_lock);
			add_hugetlb_page(h, head, false);
			h->max_huge_pages++;
			spin_unlock_irq(&hugetlb_lock);
		}

		return rc;
	}
out:
	spin_unlock_irq(&hugetlb_lock);
	return rc;
}
