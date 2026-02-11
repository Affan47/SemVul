gtkhash_properties_hash_funcs_supported(struct page_s *page)
{
	int supported = 0;

	for (int i = 0; i < HASH_FUNCS_N; i++) {
		if (page->funcs[i].supported)
			supported++;
	}

	return supported;
}
