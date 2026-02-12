static inline vm_fault_t handle_mm_fault(struct vm_area_struct *vma,
		unsigned long address, unsigned int flags)
{

	BUG();
	return VM_FAULT_SIGBUS;
}
