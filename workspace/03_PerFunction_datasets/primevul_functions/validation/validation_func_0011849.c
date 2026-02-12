int zap_huge_pud(struct mmu_gather *tlb, struct vm_area_struct *vma,
		 pud_t *pud, unsigned long addr)
{
	spinlock_t *ptl;

	ptl = __pud_trans_huge_lock(pud, vma);
	if (!ptl)
		return 0;


	pudp_huge_get_and_clear_full(tlb->mm, addr, pud, tlb->fullmm);
	tlb_remove_pud_tlb_entry(tlb, pud, addr);
	if (vma_is_special_huge(vma)) {
		spin_unlock(ptl);

	} else {

		BUG();
	}
	return 1;
}
