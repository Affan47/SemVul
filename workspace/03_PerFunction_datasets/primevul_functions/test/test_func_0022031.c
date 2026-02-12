int __pte_alloc(struct mm_struct *mm, pmd_t *pmd, unsigned long address)
{
	pgtable_t new = pte_alloc_one(mm, address);
	if (!new)
		return -ENOMEM;


	smp_wmb();

	spin_lock(&mm->page_table_lock);
	if (!pmd_present(*pmd)) {
		mm->nr_ptes++;
		pmd_populate(mm, pmd, new);
		new = NULL;
	}
	spin_unlock(&mm->page_table_lock);
	if (new)
		pte_free(mm, new);
	return 0;
}
