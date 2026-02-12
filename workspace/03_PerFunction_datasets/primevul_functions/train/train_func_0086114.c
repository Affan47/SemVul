static inline bool page_is_pfmemalloc(struct page *page)
{


	return page->index == -1UL;
}
