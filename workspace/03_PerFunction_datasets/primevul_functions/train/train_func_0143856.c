int memory_failure(unsigned long pfn, int flags)
{
	struct page *p;
	struct page *hpage;
	struct page *orig_head;
	struct dev_pagemap *pgmap;
	int res;
	unsigned long page_flags;

	if (!sysctl_memory_failure_recovery)
		panic("Memory failure on page %lx", pfn);

	if (!pfn_valid(pfn)) {
		pr_err("Memory failure: %#lx: memory outside kernel control\n",
			pfn);
		return -ENXIO;
	}

	pgmap = get_dev_pagemap(pfn, NULL);
	if (pgmap)
		return memory_failure_dev_pagemap(pfn, flags, pgmap);

	p = pfn_to_page(pfn);
	if (PageHuge(p))
		return memory_failure_hugetlb(pfn, flags);
	if (TestSetPageHWPoison(p)) {
		pr_err("Memory failure: %#lx: already hardware poisoned\n",
			pfn);
		return 0;
	}

	orig_head = hpage = compound_head(p);
	num_poisoned_pages_inc();


	if (!(flags & MF_COUNT_INCREASED) && !get_hwpoison_page(p)) {
		if (is_free_buddy_page(p)) {
			action_result(pfn, MF_MSG_BUDDY, MF_DELAYED);
			return 0;
		} else {
			action_result(pfn, MF_MSG_KERNEL_HIGH_ORDER, MF_IGNORED);
			return -EBUSY;
		}
	}

	if (PageTransHuge(hpage)) {
		lock_page(p);
		if (!PageAnon(p) || unlikely(split_huge_page(p))) {
			unlock_page(p);
			if (!PageAnon(p))
				pr_err("Memory failure: %#lx: non anonymous thp\n",
					pfn);
			else
				pr_err("Memory failure: %#lx: thp split failed\n",
					pfn);
			if (TestClearPageHWPoison(p))
				num_poisoned_pages_dec();
			put_hwpoison_page(p);
			return -EBUSY;
		}
		unlock_page(p);
		VM_BUG_ON_PAGE(!page_count(p), p);
		hpage = compound_head(p);
	}


	shake_page(p, 0);

	if (!PageLRU(p) && is_free_buddy_page(p)) {
		if (flags & MF_COUNT_INCREASED)
			action_result(pfn, MF_MSG_BUDDY, MF_DELAYED);
		else
			action_result(pfn, MF_MSG_BUDDY_2ND, MF_DELAYED);
		return 0;
	}

	lock_page(p);


	if (PageCompound(p) && compound_head(p) != orig_head) {
		action_result(pfn, MF_MSG_DIFFERENT_COMPOUND, MF_IGNORED);
		res = -EBUSY;
		goto out;
	}


	if (PageHuge(p))
		page_flags = hpage->flags;
	else
		page_flags = p->flags;


	if (!PageHWPoison(p)) {
		pr_err("Memory failure: %#lx: just unpoisoned\n", pfn);
		num_poisoned_pages_dec();
		unlock_page(p);
		put_hwpoison_page(p);
		return 0;
	}
	if (hwpoison_filter(p)) {
		if (TestClearPageHWPoison(p))
			num_poisoned_pages_dec();
		unlock_page(p);
		put_hwpoison_page(p);
		return 0;
	}

	if (!PageTransTail(p) && !PageLRU(p))
		goto identify_page_state;


	wait_on_page_writeback(p);


	if (!hwpoison_user_mappings(p, pfn, flags, &hpage)) {
		action_result(pfn, MF_MSG_UNMAP_FAILED, MF_IGNORED);
		res = -EBUSY;
		goto out;
	}


	if (PageLRU(p) && !PageSwapCache(p) && p->mapping == NULL) {
		action_result(pfn, MF_MSG_TRUNCATED_LRU, MF_IGNORED);
		res = -EBUSY;
		goto out;
	}

identify_page_state:
	res = identify_page_state(pfn, p, page_flags);
out:
	unlock_page(p);
	return res;
}
