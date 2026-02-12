static inline int use_zero_page(struct vm_area_struct *vma)
{


	if (vma->vm_flags & (VM_LOCKED | VM_SHARED))
		return 0;


	return !vma->vm_ops ||
		(!vma->vm_ops->fault && !vma->vm_ops->nopfn);
}
