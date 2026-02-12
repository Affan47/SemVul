static int me_pagecache_dirty(struct page *p, unsigned long pfn)
{
	struct address_space *mapping = page_mapping(p);

	SetPageError(p);

	if (mapping) {


		mapping_set_error(mapping, -EIO);
	}

	return me_pagecache_clean(p, pfn);
}
