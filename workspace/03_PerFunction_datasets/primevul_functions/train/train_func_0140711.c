static inline struct list_head *page_deferred_list(struct page *page)
{


	return (struct list_head *)&page[2].mapping;
}
