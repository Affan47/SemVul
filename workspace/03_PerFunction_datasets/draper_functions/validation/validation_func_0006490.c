fi_get_ranges(gnet_fi_t fih)
{
    fileinfo_t *fi = file_info_find_by_handle(fih);
	GSList *ranges = NULL;
	const http_range_t *r;

    file_info_check(fi);

	HTTP_RANGE_FOREACH(fi->seen_on_network, r) {
		http_range_t *range;

        WALLOC(range);
        range->start = r->start;
        range->end   = r->end;

		ranges = g_slist_prepend(ranges, range);
	}

    return g_slist_reverse(ranges);
}
