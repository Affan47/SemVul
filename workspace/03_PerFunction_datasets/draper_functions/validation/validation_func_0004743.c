page_is_cached(void)
{
	int i;

	for (i = 0; i < LKCD_CACHED_PAGES; i++) {

		if (!LKCD_VALID_PAGE(lkcd->page_cache_hdr[i].pg_flags))
			continue;

		if (lkcd->page_cache_hdr[i].pg_addr == lkcd->curpaddr) {
			lkcd->page_cache_hdr[i].pg_hit_count++;
			lkcd->curbufptr = lkcd->page_cache_hdr[i].pg_bufptr;
			lkcd->cached_reads++;
			return TRUE;
		}
	}

	return FALSE;
}
