static int soft_offline_huge_page(struct page *page, int flags)
{
	int ret;
	unsigned long pfn = page_to_pfn(page);
	struct page *hpage = compound_head(page);
	LIST_HEAD(pagelist);


	lock_page(hpage);
	if (PageHWPoison(hpage)) {
		unlock_page(hpage);
		put_hwpoison_page(hpage);
		pr_info("soft offline: %#lx hugepage already poisoned\n", pfn);
		return -EBUSY;
	}
	unlock_page(hpage);

	ret = isolate_huge_page(hpage, &pagelist);


	put_hwpoison_page(hpage);
	if (!ret) {
		pr_info("soft offline: %#lx hugepage failed to isolate\n", pfn);
		return -EBUSY;
	}

	ret = migrate_pages(&pagelist, new_page, NULL, MPOL_MF_MOVE_ALL,
				MIGRATE_SYNC, MR_MEMORY_FAILURE);
	if (ret) {
		pr_info("soft offline: %#lx: hugepage migration failed %d, type %lx (%pGp)\n",
			pfn, ret, page->flags, &page->flags);
		if (!list_empty(&pagelist))
			putback_movable_pages(&pagelist);
		if (ret > 0)
			ret = -EIO;
	} else {


		ret = dissolve_free_huge_page(page);
		if (!ret) {
			if (set_hwpoison_free_buddy_page(page))
				num_poisoned_pages_inc();
		}
	}
	return ret;
}
