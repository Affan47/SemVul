long si_mem_available(void)
{
	long available;
	unsigned long pagecache;
	unsigned long wmark_low = 0;
	unsigned long pages[NR_LRU_LISTS];
	struct zone *zone;
	int lru;

	for (lru = LRU_BASE; lru < NR_LRU_LISTS; lru++)
		pages[lru] = global_node_page_state(NR_LRU_BASE + lru);

	for_each_zone(zone)
		wmark_low += zone->watermark[WMARK_LOW];


	available = global_zone_page_state(NR_FREE_PAGES) - totalreserve_pages;


	pagecache = pages[LRU_ACTIVE_FILE] + pages[LRU_INACTIVE_FILE];
	pagecache -= min(pagecache / 2, wmark_low);
	available += pagecache;


	available += global_node_page_state(NR_SLAB_RECLAIMABLE) -
		     min(global_node_page_state(NR_SLAB_RECLAIMABLE) / 2,
			 wmark_low);

	if (available < 0)
		available = 0;
	return available;
}
