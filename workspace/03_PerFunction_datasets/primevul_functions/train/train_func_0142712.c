void unpin_user_pages_dirty_lock(struct page **pages, unsigned long npages,
				 bool make_dirty)
{
	unsigned long index;


	if (!make_dirty) {
		unpin_user_pages(pages, npages);
		return;
	}

	for (index = 0; index < npages; index++) {
		struct page *page = compound_head(pages[index]);


		if (!PageDirty(page))
			set_page_dirty_lock(page);
		unpin_user_page(page);
	}
}
