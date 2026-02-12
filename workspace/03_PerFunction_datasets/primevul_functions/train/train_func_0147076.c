static int move_freepages(struct zone *zone,
			  struct page *start_page, struct page *end_page,
			  int migratetype, int *num_movable)
{
	struct page *page;
	unsigned int order;
	int pages_moved = 0;

#ifndef CONFIG_HOLES_IN_ZONE


	VM_BUG_ON(page_zone(start_page) != page_zone(end_page));
#endif

	if (num_movable)
		*num_movable = 0;

	for (page = start_page; page <= end_page;) {
		if (!pfn_valid_within(page_to_pfn(page))) {
			page++;
			continue;
		}


		VM_BUG_ON_PAGE(page_to_nid(page) != zone_to_nid(zone), page);

		if (!PageBuddy(page)) {


			if (num_movable &&
					(PageLRU(page) || __PageMovable(page)))
				(*num_movable)++;

			page++;
			continue;
		}

		order = page_order(page);
		list_move(&page->lru,
			  &zone->free_area[order].free_list[migratetype]);
		page += 1 << order;
		pages_moved += 1 << order;
	}

	return pages_moved;
}
