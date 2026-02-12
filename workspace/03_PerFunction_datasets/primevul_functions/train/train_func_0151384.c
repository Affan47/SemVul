static int hwpoison_user_mappings(struct page *p, unsigned long pfn,
				  int trapno, int flags, struct page **hpagep)
{
	enum ttu_flags ttu = TTU_UNMAP | TTU_IGNORE_MLOCK | TTU_IGNORE_ACCESS;
	struct address_space *mapping;
	LIST_HEAD(tokill);
	int ret;
	int kill = 1, forcekill;
	struct page *hpage = *hpagep;


	if (PageReserved(p) || PageSlab(p))
		return SWAP_SUCCESS;
	if (!(PageLRU(hpage) || PageHuge(p)))
		return SWAP_SUCCESS;


	if (!page_mapped(hpage))
		return SWAP_SUCCESS;

	if (PageKsm(p)) {
		pr_err("Memory failure: %#lx: can't handle KSM pages.\n", pfn);
		return SWAP_FAIL;
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

	ret = try_to_unmap(hpage, ttu);
	if (ret != SWAP_SUCCESS)
		pr_err("Memory failure: %#lx: failed to unmap page (mapcount=%d)\n",
		       pfn, page_mapcount(hpage));


	forcekill = PageDirty(hpage) || (flags & MF_MUST_KILL);
	kill_procs(&tokill, forcekill, trapno,
		      ret != SWAP_SUCCESS, p, pfn, flags);

	return ret;
}
