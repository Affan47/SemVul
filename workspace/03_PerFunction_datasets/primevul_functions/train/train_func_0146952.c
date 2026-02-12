static void steal_suitable_fallback(struct zone *zone, struct page *page,
					int start_type, bool whole_block)
{
	unsigned int current_order = page_order(page);
	struct free_area *area;
	int free_pages, movable_pages, alike_pages;
	int old_block_type;

	old_block_type = get_pageblock_migratetype(page);


	if (is_migrate_highatomic(old_block_type))
		goto single_page;


	if (current_order >= pageblock_order) {
		change_pageblock_range(page, current_order, start_type);
		goto single_page;
	}


	if (!whole_block)
		goto single_page;

	free_pages = move_freepages_block(zone, page, start_type,
						&movable_pages);


	if (start_type == MIGRATE_MOVABLE) {
		alike_pages = movable_pages;
	} else {


		if (old_block_type == MIGRATE_MOVABLE)
			alike_pages = pageblock_nr_pages
						- (free_pages + movable_pages);
		else
			alike_pages = 0;
	}


	if (!free_pages)
		goto single_page;


	if (free_pages + alike_pages >= (1 << (pageblock_order-1)) ||
			page_group_by_mobility_disabled)
		set_pageblock_migratetype(page, start_type);

	return;

single_page:
	area = &zone->free_area[current_order];
	list_move(&page->lru, &area->free_list[start_type]);
}
