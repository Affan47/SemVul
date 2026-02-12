access_error(unsigned long error_code, struct vm_area_struct *vma)
{

	bool foreign = false;


	if (error_code & X86_PF_PK)
		return 1;


	if (!arch_vma_access_permitted(vma, (error_code & X86_PF_WRITE),
				       (error_code & X86_PF_INSTR), foreign))
		return 1;

	if (error_code & X86_PF_WRITE) {

		if (unlikely(!(vma->vm_flags & VM_WRITE)))
			return 1;
		return 0;
	}


	if (unlikely(error_code & X86_PF_PROT))
		return 1;


	if (unlikely(!(vma->vm_flags & (VM_READ | VM_EXEC | VM_WRITE))))
		return 1;

	return 0;
}
