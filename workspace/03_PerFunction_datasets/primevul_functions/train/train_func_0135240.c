static inline bool vma_is_foreign(struct vm_area_struct *vma)
{
	if (!current->mm)
		return true;


	if (current->mm != vma->vm_mm)
		return true;

	return false;
}
