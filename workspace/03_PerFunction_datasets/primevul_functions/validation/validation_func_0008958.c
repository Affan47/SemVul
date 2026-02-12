static unsigned long move_vma(struct vm_area_struct *vma,
		unsigned long old_addr, unsigned long old_len,
		unsigned long new_len, unsigned long new_addr,
		bool *locked, unsigned long flags,
		struct vm_userfaultfd_ctx *uf, struct list_head *uf_unmap)
{
	struct mm_struct *mm = vma->vm_mm;
	struct vm_area_struct *new_vma;
	unsigned long vm_flags = vma->vm_flags;
	unsigned long new_pgoff;
	unsigned long moved_len;
	unsigned long excess = 0;
	unsigned long hiwater_vm;
	int split = 0;
	int err;
	bool need_rmap_locks;


	if (mm->map_count >= sysctl_max_map_count - 3)
		return -ENOMEM;


	err = ksm_madvise(vma, old_addr, old_addr + old_len,
						MADV_UNMERGEABLE, &vm_flags);
	if (err)
		return err;

	new_pgoff = vma->vm_pgoff + ((old_addr - vma->vm_start) >> PAGE_SHIFT);
	new_vma = copy_vma(&vma, new_addr, new_len, new_pgoff,
			   &need_rmap_locks);
	if (!new_vma)
		return -ENOMEM;

	moved_len = move_page_tables(vma, old_addr, new_vma, new_addr, old_len,
				     need_rmap_locks);
	if (moved_len < old_len) {
		err = -ENOMEM;
	} else if (vma->vm_ops && vma->vm_ops->mremap) {
		err = vma->vm_ops->mremap(new_vma);
	}

	if (unlikely(err)) {


		move_page_tables(new_vma, new_addr, vma, old_addr, moved_len,
				 true);
		vma = new_vma;
		old_len = new_len;
		old_addr = new_addr;
		new_addr = err;
	} else {
		mremap_userfaultfd_prep(new_vma, uf);
		arch_remap(mm, old_addr, old_addr + old_len,
			   new_addr, new_addr + new_len);
	}


	if (vm_flags & VM_ACCOUNT) {
		vma->vm_flags &= ~VM_ACCOUNT;
		excess = vma->vm_end - vma->vm_start - old_len;
		if (old_addr > vma->vm_start &&
		    old_addr + old_len < vma->vm_end)
			split = 1;
	}


	hiwater_vm = mm->hiwater_vm;
	vm_stat_account(mm, vma->vm_flags, new_len >> PAGE_SHIFT);


	if (unlikely(vma->vm_flags & VM_PFNMAP))
		untrack_pfn_moved(vma);

	if (unlikely(!err && (flags & MREMAP_DONTUNMAP))) {
		if (vm_flags & VM_ACCOUNT) {

			vma->vm_flags |= VM_ACCOUNT;

			vm_acct_memory(new_len >> PAGE_SHIFT);
		}


		if (split && new_vma == vma)
			split = 0;


		vma->vm_flags &= VM_LOCKED_CLEAR_MASK;


		goto out;
	}

	if (do_munmap(mm, old_addr, old_len, uf_unmap) < 0) {

		vm_unacct_memory(excess >> PAGE_SHIFT);
		excess = 0;
	}

	if (vm_flags & VM_LOCKED) {
		mm->locked_vm += new_len >> PAGE_SHIFT;
		*locked = true;
	}
out:
	mm->hiwater_vm = hiwater_vm;


	if (excess) {
		vma->vm_flags |= VM_ACCOUNT;
		if (split)
			vma->vm_next->vm_flags |= VM_ACCOUNT;
	}

	return new_addr;
}
