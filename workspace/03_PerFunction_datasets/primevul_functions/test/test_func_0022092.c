static int fallback_migrate_page(struct address_space *mapping,
	struct page *newpage, struct page *page)
{
	if (PageDirty(page))
		return writeout(mapping, page);


	if (PagePrivate(page) &&
	    !try_to_release_page(page, GFP_KERNEL))
		return -EAGAIN;

	return migrate_page(mapping, newpage, page);
}
