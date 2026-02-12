int memory_failure(unsigned long pfn, int trapno, int flags)
{
	struct page_state *ps;
	struct page *p;
	struct page *hpage;
	struct page *orig_head;
	int res;
	unsigned int nr_pages;
	unsigned long page_flags;

	if (!sysctl_memory_failure_recovery)
		panic("Memory failure from trap %d on page %lx", trapno, pfn);

	if (!pfn_valid(pfn)) {
		pr_err("Memory failure: %#lx: memory outside kernel control\n",
			pfn);
		return -ENXIO;
	}

	p = pfn_to_page(pfn);
	orig_head = hpage = compound_head(p);
	if (TestSetPageHWPoison(p)) {
		pr_err("Memory failure: %#lx: already hardware poisoned\n",
			pfn);
		return 0;
	}


	if (PageHuge(p))
		nr_pages = 1 << compound_order(hpage);
	else
		nr_pages = 1;
	num_poisoned_pages_add(nr_pages);


	if (!(flags & MF_COUNT_INCREASED) && !get_hwpoison_page(p)) {
		if (is_free_buddy_page(p)) {
			action_result(pfn, MF_MSG_BUDDY, MF_DELAYED);
			return 0;
		} else if (PageHuge(hpage)) {


			lock_page(hpage);
			if (PageHWPoison(hpage)) {
				if ((hwpoison_filter(p) && TestClearPageHWPoison(p))
				    || (p != hpage && TestSetPageHWPoison(hpage))) {
					num_poisoned_pages_sub(nr_pages);
					unlock_page(hpage);
					return 0;
				}
			}
			set_page_hwpoison_huge_page(hpage);
			res = dequeue_hwpoisoned_huge_page(hpage);
			action_result(pfn, MF_MSG_FREE_HUGE,
				      res ? MF_IGNORED : MF_DELAYED);
			unlock_page(hpage);
			return res;
		} else {
			action_result(pfn, MF_MSG_KERNEL_HIGH_ORDER, MF_IGNORED);
			return -EBUSY;
		}
	}

	if (!PageHuge(p) && PageTransHuge(hpage)) {
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
				num_poisoned_pages_sub(nr_pages);
			put_hwpoison_page(p);
			return -EBUSY;
		}
		unlock_page(p);
		VM_BUG_ON_PAGE(!page_count(p), p);
		hpage = compound_head(p);
	}


	if (!PageHuge(p)) {
		if (!PageLRU(p))
			shake_page(p, 0);
		if (!PageLRU(p)) {


			if (is_free_buddy_page(p)) {
				if (flags & MF_COUNT_INCREASED)
					action_result(pfn, MF_MSG_BUDDY, MF_DELAYED);
				else
					action_result(pfn, MF_MSG_BUDDY_2ND,
						      MF_DELAYED);
				return 0;
			}
		}
	}

	lock_page(hpage);


	if (PageCompound(p) && compound_head(p) != orig_head) {
		action_result(pfn, MF_MSG_DIFFERENT_COMPOUND, MF_IGNORED);
		res = -EBUSY;
		goto out;
	}


	page_flags = p->flags;


	if (!PageHWPoison(p)) {
		pr_err("Memory failure: %#lx: just unpoisoned\n", pfn);
		num_poisoned_pages_sub(nr_pages);
		unlock_page(hpage);
		put_hwpoison_page(hpage);
		return 0;
	}
	if (hwpoison_filter(p)) {
		if (TestClearPageHWPoison(p))
			num_poisoned_pages_sub(nr_pages);
		unlock_page(hpage);
		put_hwpoison_page(hpage);
		return 0;
	}

	if (!PageHuge(p) && !PageTransTail(p) && !PageLRU(p))
		goto identify_page_state;


	if (PageHuge(p) && PageTail(p) && TestSetPageHWPoison(hpage)) {
		action_result(pfn, MF_MSG_POISONED_HUGE, MF_IGNORED);
		unlock_page(hpage);
		put_hwpoison_page(hpage);
		return 0;
	}


	if (PageHuge(p))
		set_page_hwpoison_huge_page(hpage);


	wait_on_page_writeback(p);


	if (hwpoison_user_mappings(p, pfn, trapno, flags, &hpage)
	    != SWAP_SUCCESS) {
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
	res = -EBUSY;


	for (ps = error_states;; ps++)
		if ((p->flags & ps->mask) == ps->res)
			break;

	page_flags |= (p->flags & (1UL << PG_dirty));

	if (!ps->mask)
		for (ps = error_states;; ps++)
			if ((page_flags & ps->mask) == ps->res)
				break;
	res = page_action(ps, p, pfn);
out:
	unlock_page(hpage);
	return res;
}
