static int memory_failure_dev_pagemap(unsigned long pfn, int flags,
		struct dev_pagemap *pgmap)
{
	struct page *page = pfn_to_page(pfn);
	const bool unmap_success = true;
	unsigned long size = 0;
	struct to_kill *tk;
	LIST_HEAD(tokill);
	int rc = -EBUSY;
	loff_t start;
	dax_entry_t cookie;


	cookie = dax_lock_page(page);
	if (!cookie)
		goto out;

	if (hwpoison_filter(page)) {
		rc = 0;
		goto unlock;
	}

	switch (pgmap->type) {
	case MEMORY_DEVICE_PRIVATE:
	case MEMORY_DEVICE_PUBLIC:


		goto unlock;
	default:
		break;
	}


	SetPageHWPoison(page);


	flags |= MF_ACTION_REQUIRED | MF_MUST_KILL;
	collect_procs(page, &tokill, flags & MF_ACTION_REQUIRED);

	list_for_each_entry(tk, &tokill, nd)
		if (tk->size_shift)
			size = max(size, 1UL << tk->size_shift);
	if (size) {


		start = (page->index << PAGE_SHIFT) & ~(size - 1);
		unmap_mapping_range(page->mapping, start, start + size, 0);
	}
	kill_procs(&tokill, flags & MF_MUST_KILL, !unmap_success, pfn, flags);
	rc = 0;
unlock:
	dax_unlock_page(page, cookie);
out:

	put_dev_pagemap(pgmap);
	action_result(pfn, MF_MSG_DAX, rc ? MF_FAILED : MF_RECOVERED);
	return rc;
}
