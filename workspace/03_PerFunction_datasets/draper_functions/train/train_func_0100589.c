acct_isolated(struct zone *zone, struct compact_control *cc)
{
	struct page *page;
	unsigned int count[2] = { 0, };

	if (list_empty(&cc->migratepages))
		return;

	list_for_each_entry(page, &cc->migratepages, lru)
		count[!!page_is_file_cache(page)]++;

	mod_zone_page_state(zone, NR_ISOLATED_ANON, count[0]);
	mod_zone_page_state(zone, NR_ISOLATED_FILE, count[1]);
}
