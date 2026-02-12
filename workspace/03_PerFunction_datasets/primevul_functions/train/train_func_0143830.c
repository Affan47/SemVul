static int me_huge_page(struct page *p, unsigned long pfn)
{
	int res = 0;
	struct page *hpage = compound_head(p);
	struct address_space *mapping;

	if (!PageHuge(hpage))
		return MF_DELAYED;

	mapping = page_mapping(hpage);
	if (mapping) {
		res = truncate_error_page(hpage, pfn, mapping);
	} else {
		unlock_page(hpage);


		if (PageAnon(hpage))
			put_page(hpage);
		dissolve_free_huge_page(p);
		res = MF_RECOVERED;
		lock_page(hpage);
	}

	return res;
}
