static inline pte_t __ptep_modify_prot_start(struct mm_struct *mm,
					     unsigned long addr,
					     pte_t *ptep)
{


	return ptep_get_and_clear(mm, addr, ptep);
}
