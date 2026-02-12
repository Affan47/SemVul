static int me_pagecache_clean(struct page *p, unsigned long pfn)
{
	struct address_space *mapping;

	delete_from_lru_cache(p);


	if (PageAnon(p))
		return MF_RECOVERED;


	mapping = page_mapping(p);
	if (!mapping) {


		return MF_FAILED;
	}


	return truncate_error_page(p, pfn, mapping);
}
