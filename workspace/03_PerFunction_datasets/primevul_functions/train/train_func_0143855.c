static bool hwpoison_user_mappings(struct page *p, unsigned long pfn,
				  int flags, struct page **hpagep)
{
	enum ttu_flags ttu = TTU_IGNORE_MLOCK | TTU_IGNORE_ACCESS;
	struct address_space *mapping;
	LIST_HEAD(tokill);
	bool unmap_success;
	int kill = 1, forcekill;
	struct page *hpage = *hpagep;
	bool mlocked = PageMlocked(hpage);


	if (PageReserved(p) || PageSlab(p))
		return true;
	if (!(PageLRU(hpage) || PageHuge(p)))
		return true;


	if (!page_mapped(hpage))
		return true;

	if (PageKsm(p)) {
		pr_err("Memory failure: %#lx: can't handle KSM pages.\n", pfn);
		return false;
	}

	if (PageSwapCache(p)) {
		pr_err("Memory failure: %#lx: keeping poisoned page in swap cache\n",
			pfn);
		ttu |= TTU_IGNORE_HWPOISON;
	}


	mapping = page_mapping(hpage);
	if (!(flags & MF_MUST_KILL) && !PageDirty(hpage) && mapping &&
	    mapping_cap_writeback_dirty(mapping)) {
		if (page_mkclean(hpage)) {
			SetPageDirty(hpage);
		} else {
			kill = 0;
			ttu |= TTU_IGNORE_HWPOISON;
			pr_info("Memory failure: %#lx: corrupted page was clean: dropped without side effects\n",
				pfn);
		}
	}


	if (kill)
		collect_procs(hpage, &tokill, flags & MF_ACTION_REQUIRED);

	unmap_success = try_to_unmap(hpage, ttu);
	if (!unmap_success)
		pr_err("Memory failure: %#lx: failed to unmap page (mapcount=%d)\n",
		       pfn, page_mapcount(hpage));


	if (mlocked)
		shake_page(hpage, 0);


	forcekill = PageDirty(hpage) || (flags & MF_MUST_KILL);
	kill_procs(&tokill, forcekill, !unmap_success, pfn, flags);

	return unmap_success;
}
