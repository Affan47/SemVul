static struct page *alloc_surplus_huge_page(struct hstate *h, gfp_t gfp_mask,
		int nid, nodemask_t *nmask, bool zero_ref)
{
	struct page *page = NULL;
	bool retry = false;

	if (hstate_is_gigantic(h))
		return NULL;

	spin_lock_irq(&hugetlb_lock);
	if (h->surplus_huge_pages >= h->nr_overcommit_huge_pages)
		goto out_unlock;
	spin_unlock_irq(&hugetlb_lock);

retry:
	page = alloc_fresh_huge_page(h, gfp_mask, nid, nmask, NULL);
	if (!page)
		return NULL;

	spin_lock_irq(&hugetlb_lock);


	if (h->surplus_huge_pages >= h->nr_overcommit_huge_pages) {
		SetHPageTemporary(page);
		spin_unlock_irq(&hugetlb_lock);
		put_page(page);
		return NULL;
	}

	if (zero_ref) {


		SetHPageTemporary(page);
		if (!put_page_testzero(page)) {


			pr_info("HugeTLB unexpected inflated ref count on freshly allocated page\n");
			spin_unlock_irq(&hugetlb_lock);
			if (retry)
				return NULL;

			retry = true;
			goto retry;
		}
		ClearHPageTemporary(page);
	}

	h->surplus_huge_pages++;
	h->surplus_huge_pages_node[page_to_nid(page)]++;

out_unlock:
	spin_unlock_irq(&hugetlb_lock);

	return page;
}
