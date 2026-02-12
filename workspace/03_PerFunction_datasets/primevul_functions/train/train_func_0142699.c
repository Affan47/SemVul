static __maybe_unused struct page *try_grab_compound_head(struct page *page,
							  int refs,
							  unsigned int flags)
{
	if (flags & FOLL_GET)
		return try_get_compound_head(page, refs);
	else if (flags & FOLL_PIN) {
		int orig_refs = refs;


		if (unlikely(flags & FOLL_LONGTERM) &&
				is_migrate_cma_page(page))
			return NULL;


		if (!hpage_pincount_available(page))
			refs *= GUP_PIN_COUNTING_BIAS;

		page = try_get_compound_head(page, refs);
		if (!page)
			return NULL;

		if (hpage_pincount_available(page))
			hpage_pincount_add(page, refs);

		mod_node_page_state(page_pgdat(page), NR_FOLL_PIN_ACQUIRED,
				    orig_refs);

		return page;
	}

	WARN_ON_ONCE(1);
	return NULL;
}
