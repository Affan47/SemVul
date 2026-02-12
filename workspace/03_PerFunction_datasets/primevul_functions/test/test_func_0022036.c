static void remove_migration_pte(struct vm_area_struct *vma,
		struct page *old, struct page *new)
{
	struct mm_struct *mm = vma->vm_mm;
	swp_entry_t entry;
 	pgd_t *pgd;
 	pud_t *pud;
 	pmd_t *pmd;
	pte_t *ptep, pte;
 	spinlock_t *ptl;
	unsigned long addr = page_address_in_vma(new, vma);

	if (addr == -EFAULT)
		return;

 	pgd = pgd_offset(mm, addr);
	if (!pgd_present(*pgd))
                return;

	pud = pud_offset(pgd, addr);
	if (!pud_present(*pud))
                return;

	pmd = pmd_offset(pud, addr);
	if (!pmd_present(*pmd))
		return;

	ptep = pte_offset_map(pmd, addr);

	if (!is_swap_pte(*ptep)) {
		pte_unmap(ptep);
 		return;
 	}

 	ptl = pte_lockptr(mm, pmd);
 	spin_lock(ptl);
	pte = *ptep;
	if (!is_swap_pte(pte))
		goto out;

	entry = pte_to_swp_entry(pte);

	if (!is_migration_entry(entry) || migration_entry_to_page(entry) != old)
		goto out;


	mem_cgroup_charge(new, mm, GFP_ATOMIC);

	get_page(new);
	pte = pte_mkold(mk_pte(new, vma->vm_page_prot));
	if (is_write_migration_entry(entry))
		pte = pte_mkwrite(pte);
	flush_cache_page(vma, addr, pte_pfn(pte));
	set_pte_at(mm, addr, ptep, pte);

	if (PageAnon(new))
		page_add_anon_rmap(new, vma, addr);
	else
		page_add_file_rmap(new);


	update_mmu_cache(vma, addr, pte);

out:
	pte_unmap_unlock(ptep, ptl);
}
