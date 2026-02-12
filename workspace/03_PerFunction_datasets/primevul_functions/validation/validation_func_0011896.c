static inline int pmd_move_must_withdraw(spinlock_t *new_pmd_ptl,
					 spinlock_t *old_pmd_ptl,
					 struct vm_area_struct *vma)
{


	return (new_pmd_ptl != old_pmd_ptl) && vma_is_anonymous(vma);
}
