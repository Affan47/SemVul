ia64_elf32_init (struct pt_regs *regs)
{
	struct vm_area_struct *vma;


	vma = kmem_cache_zalloc(vm_area_cachep, GFP_KERNEL);
	if (vma) {
		vma->vm_mm = current->mm;
		vma->vm_start = IA32_GDT_OFFSET;
		vma->vm_end = vma->vm_start + PAGE_SIZE;
		vma->vm_page_prot = PAGE_SHARED;
		vma->vm_flags = VM_READ|VM_MAYREAD|VM_RESERVED;
		vma->vm_ops = &ia32_shared_page_vm_ops;
		down_write(&current->mm->mmap_sem);
		{
			if (insert_vm_struct(current->mm, vma)) {
				kmem_cache_free(vm_area_cachep, vma);
				up_write(&current->mm->mmap_sem);
				BUG();
			}
		}
		up_write(&current->mm->mmap_sem);
	}


	vma = kmem_cache_zalloc(vm_area_cachep, GFP_KERNEL);
	if (vma) {
		vma->vm_mm = current->mm;
		vma->vm_start = IA32_GATE_OFFSET;
		vma->vm_end = vma->vm_start + PAGE_SIZE;
		vma->vm_page_prot = PAGE_COPY_EXEC;
		vma->vm_flags = VM_READ | VM_MAYREAD | VM_EXEC
				| VM_MAYEXEC | VM_RESERVED;
		vma->vm_ops = &ia32_gate_page_vm_ops;
		down_write(&current->mm->mmap_sem);
		{
			if (insert_vm_struct(current->mm, vma)) {
				kmem_cache_free(vm_area_cachep, vma);
				up_write(&current->mm->mmap_sem);
				BUG();
			}
		}
		up_write(&current->mm->mmap_sem);
	}


	vma = kmem_cache_zalloc(vm_area_cachep, GFP_KERNEL);
	if (vma) {
		vma->vm_mm = current->mm;
		vma->vm_start = IA32_LDT_OFFSET;
		vma->vm_end = vma->vm_start + PAGE_ALIGN(IA32_LDT_ENTRIES*IA32_LDT_ENTRY_SIZE);
		vma->vm_page_prot = PAGE_SHARED;
		vma->vm_flags = VM_READ|VM_WRITE|VM_MAYREAD|VM_MAYWRITE;
		down_write(&current->mm->mmap_sem);
		{
			if (insert_vm_struct(current->mm, vma)) {
				kmem_cache_free(vm_area_cachep, vma);
				up_write(&current->mm->mmap_sem);
				BUG();
			}
		}
		up_write(&current->mm->mmap_sem);
	}

	ia64_psr(regs)->ac = 0;
	regs->loadrs = 0;


	regs->r8 = 0;
	regs->r11 = 0;
	regs->r9 = 0;
	regs->r10 = 0;
	regs->r13 = 0;
	regs->r14 = 0;
	regs->r15 = 0;

	current->thread.eflag = IA32_EFLAG;
	current->thread.fsr = IA32_FSR_DEFAULT;
	current->thread.fcr = IA32_FCR_DEFAULT;
	current->thread.fir = 0;
	current->thread.fdr = 0;


	regs->r31 = IA32_SEG_UNSCRAMBLE(IA32_SEG_DESCRIPTOR(IA32_GDT_OFFSET, IA32_PAGE_SIZE - 1,
							    0, 0, 0, 1, 0, 0, 0));

	regs->r16 = (__USER_DS << 16) | __USER_DS;
	regs->r17 = (__USER_DS << 16) | __USER_CS;

	ia32_load_segment_descriptors(current);
	ia32_load_state(current);
}
