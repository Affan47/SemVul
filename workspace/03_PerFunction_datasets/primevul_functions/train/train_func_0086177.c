static inline void put_page(struct page *page)
{
	page = compound_head(page);


	if (put_devmap_managed_page(page))
		return;

	if (put_page_testzero(page))
		__put_page(page);
}
