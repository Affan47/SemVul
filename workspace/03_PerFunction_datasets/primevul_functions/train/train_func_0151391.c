static int me_pagecache_clean(struct page *p, unsigned long pfn)
{
	int err;
	int ret = MF_FAILED;
	struct address_space *mapping;

	delete_from_lru_cache(p);


	if (PageAnon(p))
		return MF_RECOVERED;


	mapping = page_mapping(p);
	if (!mapping) {


		return MF_FAILED;
	}


	if (mapping->a_ops->error_remove_page) {
		err = mapping->a_ops->error_remove_page(mapping, p);
		if (err != 0) {
			pr_info("Memory failure: %#lx: Failed to punch page: %d\n",
				pfn, err);
		} else if (page_has_private(p) &&
				!try_to_release_page(p, GFP_NOIO)) {
			pr_info("Memory failure: %#lx: failed to release buffers\n",
				pfn);
		} else {
			ret = MF_RECOVERED;
		}
	} else {


		if (invalidate_inode_page(p))
			ret = MF_RECOVERED;
		else
			pr_info("Memory failure: %#lx: Failed to invalidate\n",
				pfn);
	}
	return ret;
}
