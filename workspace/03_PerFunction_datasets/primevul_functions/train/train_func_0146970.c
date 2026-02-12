static void prep_new_page(struct page *page, unsigned int order, gfp_t gfp_flags,
							unsigned int alloc_flags)
{
	int i;

	post_alloc_hook(page, order, gfp_flags);

	if (!free_pages_prezeroed() && (gfp_flags & __GFP_ZERO))
		for (i = 0; i < (1 << order); i++)
			clear_highpage(page + i);

	if (order && (gfp_flags & __GFP_COMP))
		prep_compound_page(page, order);


	if (alloc_flags & ALLOC_NO_WATERMARKS)
		set_page_pfmemalloc(page);
	else
		clear_page_pfmemalloc(page);
}
