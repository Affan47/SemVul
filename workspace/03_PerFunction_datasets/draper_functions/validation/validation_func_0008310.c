read_dev_sector(struct block_device *bdev, sector_t n, Sector *p)
{
	struct address_space *mapping = bdev->bd_inode->i_mapping;
	struct page *page;

	page = read_mapping_page(mapping, (pgoff_t)(n >> (PAGE_CACHE_SHIFT-9)),
				 NULL);
	if (!IS_ERR(page)) {
		if (PageError(page))
			goto fail;
		p->v = page;
		return (unsigned char *)page_address(page) +  ((n & ((1 << (PAGE_CACHE_SHIFT - 9)) - 1)) << 9);
fail:
		page_cache_release(page);
	}
	p->v = NULL;
	return NULL;
}
