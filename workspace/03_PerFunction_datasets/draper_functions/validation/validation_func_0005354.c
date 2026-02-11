sync_global_pgds(unsigned long start, unsigned long end, int removed)
{
	unsigned long address;

	for (address = start; address <= end; address += PGDIR_SIZE) {
		const pgd_t *pgd_ref = pgd_offset_k(address);
		struct page *page;


		if (pgd_none(*pgd_ref) && !removed)
			continue;

		spin_lock(&pgd_lock);
		list_for_each_entry(page, &pgd_list, lru) {
			pgd_t *pgd;
			spinlock_t *pgt_lock;

			pgd = (pgd_t *)page_address(page) + pgd_index(address);

			pgt_lock = &pgd_page_get_mm(page)->page_table_lock;
			spin_lock(pgt_lock);

			if (!pgd_none(*pgd_ref) && !pgd_none(*pgd))
				BUG_ON(pgd_page_vaddr(*pgd)
				       != pgd_page_vaddr(*pgd_ref));

			if (removed) {
				if (pgd_none(*pgd_ref) && !pgd_none(*pgd))
					pgd_clear(pgd);
			} else {
				if (pgd_none(*pgd))
					set_pgd(pgd, *pgd_ref);
			}

			spin_unlock(pgt_lock);
		}
		spin_unlock(&pgd_lock);
	}
}
