static inline void cancel_dirty_page(struct page *page)
{

	if (PageDirty(page))
		__cancel_dirty_page(page);
}
