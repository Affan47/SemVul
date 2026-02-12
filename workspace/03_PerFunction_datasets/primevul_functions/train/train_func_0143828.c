int unpoison_memory(unsigned long pfn)
{
	struct page *page;
	struct page *p;
	int freeit = 0;
	static DEFINE_RATELIMIT_STATE(unpoison_rs, DEFAULT_RATELIMIT_INTERVAL,
					DEFAULT_RATELIMIT_BURST);

	if (!pfn_valid(pfn))
		return -ENXIO;

	p = pfn_to_page(pfn);
	page = compound_head(p);

	if (!PageHWPoison(p)) {
		unpoison_pr_info("Unpoison: Page was already unpoisoned %#lx\n",
				 pfn, &unpoison_rs);
		return 0;
	}

	if (page_count(page) > 1) {
		unpoison_pr_info("Unpoison: Someone grabs the hwpoison page %#lx\n",
				 pfn, &unpoison_rs);
		return 0;
	}

	if (page_mapped(page)) {
		unpoison_pr_info("Unpoison: Someone maps the hwpoison page %#lx\n",
				 pfn, &unpoison_rs);
		return 0;
	}

	if (page_mapping(page)) {
		unpoison_pr_info("Unpoison: the hwpoison page has non-NULL mapping %#lx\n",
				 pfn, &unpoison_rs);
		return 0;
	}


	if (!PageHuge(page) && PageTransHuge(page)) {
		unpoison_pr_info("Unpoison: Memory failure is now running on %#lx\n",
				 pfn, &unpoison_rs);
		return 0;
	}

	if (!get_hwpoison_page(p)) {
		if (TestClearPageHWPoison(p))
			num_poisoned_pages_dec();
		unpoison_pr_info("Unpoison: Software-unpoisoned free page %#lx\n",
				 pfn, &unpoison_rs);
		return 0;
	}

	lock_page(page);


	if (TestClearPageHWPoison(page)) {
		unpoison_pr_info("Unpoison: Software-unpoisoned page %#lx\n",
				 pfn, &unpoison_rs);
		num_poisoned_pages_dec();
		freeit = 1;
	}
	unlock_page(page);

	put_hwpoison_page(page);
	if (freeit && !(pfn == my_zero_pfn(0) && page_count(p) == 1))
		put_hwpoison_page(page);

	return 0;
}
