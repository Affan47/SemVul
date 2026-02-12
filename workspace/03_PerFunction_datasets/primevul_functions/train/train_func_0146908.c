static inline bool zone_watermark_fast(struct zone *z, unsigned int order,
		unsigned long mark, int classzone_idx, unsigned int alloc_flags)
{
	long free_pages = zone_page_state(z, NR_FREE_PAGES);
	long cma_pages = 0;

#ifdef CONFIG_CMA

	if (!(alloc_flags & ALLOC_CMA))
		cma_pages = zone_page_state(z, NR_FREE_CMA_PAGES);
#endif


	if (!order && (free_pages - cma_pages) > mark + z->lowmem_reserve[classzone_idx])
		return true;

	return __zone_watermark_ok(z, order, mark, classzone_idx, alloc_flags,
					free_pages);
}
