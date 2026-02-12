void __paginginit zero_resv_unavail(void)
{
	phys_addr_t start, end;
	unsigned long pfn;
	u64 i, pgcnt;


	pgcnt = 0;
	for_each_resv_unavail_range(i, &start, &end) {
		for (pfn = PFN_DOWN(start); pfn < PFN_UP(end); pfn++) {
			mm_zero_struct_page(pfn_to_page(pfn));
			pgcnt++;
		}
	}


	if (pgcnt)
		pr_info("Reserved but unavailable: %lld pages", pgcnt);
}
