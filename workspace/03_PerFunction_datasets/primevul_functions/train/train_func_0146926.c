static void free_pcppages_bulk(struct zone *zone, int count,
					struct per_cpu_pages *pcp)
{
	int migratetype = 0;
	int batch_free = 0;
	bool isolated_pageblocks;

	spin_lock(&zone->lock);
	isolated_pageblocks = has_isolate_pageblock(zone);

	while (count) {
		struct page *page;
		struct list_head *list;


		do {
			batch_free++;
			if (++migratetype == MIGRATE_PCPTYPES)
				migratetype = 0;
			list = &pcp->lists[migratetype];
		} while (list_empty(list));


		if (batch_free == MIGRATE_PCPTYPES)
			batch_free = count;

		do {
			int mt;

			page = list_last_entry(list, struct page, lru);

			list_del(&page->lru);

			mt = get_pcppage_migratetype(page);

			VM_BUG_ON_PAGE(is_migrate_isolate(mt), page);

			if (unlikely(isolated_pageblocks))
				mt = get_pageblock_migratetype(page);

			if (bulkfree_pcp_prepare(page))
				continue;

			__free_one_page(page, page_to_pfn(page), zone, 0, mt);
			trace_mm_page_pcpu_drain(page, 0, mt);
		} while (--count && --batch_free && !list_empty(list));
	}
	spin_unlock(&zone->lock);
}
