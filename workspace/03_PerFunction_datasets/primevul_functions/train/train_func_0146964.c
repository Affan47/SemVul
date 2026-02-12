bool has_unmovable_pages(struct zone *zone, struct page *page, int count,
			 int migratetype,
			 bool skip_hwpoisoned_pages)
{
	unsigned long pfn, iter, found;


	if (zone_idx(zone) == ZONE_MOVABLE)
		return false;


	if (is_migrate_cma(migratetype) &&
			is_migrate_cma(get_pageblock_migratetype(page)))
		return false;

	pfn = page_to_pfn(page);
	for (found = 0, iter = 0; iter < pageblock_nr_pages; iter++) {
		unsigned long check = pfn + iter;

		if (!pfn_valid_within(check))
			continue;

		page = pfn_to_page(check);

		if (PageReserved(page))
			return true;


		if (PageHuge(page)) {
			iter = round_up(iter + 1, 1<<compound_order(page)) - 1;
			continue;
		}


		if (!page_ref_count(page)) {
			if (PageBuddy(page))
				iter += (1 << page_order(page)) - 1;
			continue;
		}


		if (skip_hwpoisoned_pages && PageHWPoison(page))
			continue;

		if (__PageMovable(page))
			continue;

		if (!PageLRU(page))
			found++;


		if (found > count)
			return true;
	}
	return false;
}
