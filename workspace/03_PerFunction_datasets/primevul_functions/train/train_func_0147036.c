static inline void reset_deferred_meminit(pg_data_t *pgdat)
{
	unsigned long max_initialise;
	unsigned long reserved_lowmem;


	max_initialise = max(2UL << (30 - PAGE_SHIFT),
		(pgdat->node_spanned_pages >> 8));


	reserved_lowmem = memblock_reserved_memory_within(pgdat->node_start_pfn,
			pgdat->node_start_pfn + max_initialise);
	max_initialise += reserved_lowmem;

	pgdat->static_init_size = min(max_initialise, pgdat->node_spanned_pages);
	pgdat->first_deferred_pfn = ULONG_MAX;
}
