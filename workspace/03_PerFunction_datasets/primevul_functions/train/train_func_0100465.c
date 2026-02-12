static int maydump(struct vm_area_struct *vma)
{

	if (vma->vm_flags & (VM_IO | VM_RESERVED)) {
		kdcore("%08lx: %08lx: no (IO)", vma->vm_start, vma->vm_flags);
		return 0;
	}


	if (!(vma->vm_flags & VM_READ)) {
		kdcore("%08lx: %08lx: no (!read)", vma->vm_start, vma->vm_flags);
		return 0;
	}


	if (vma->vm_flags & VM_SHARED) {
		if (vma->vm_file->f_path.dentry->d_inode->i_nlink == 0) {
			kdcore("%08lx: %08lx: no (share)", vma->vm_start, vma->vm_flags);
			return 1;
		}

		kdcore("%08lx: %08lx: no (share)", vma->vm_start, vma->vm_flags);
		return 0;
	}

#ifdef CONFIG_MMU

	if (!vma->anon_vma) {
		kdcore("%08lx: %08lx: no (!anon)", vma->vm_start, vma->vm_flags);
		return 0;
	}
#endif

	kdcore("%08lx: %08lx: yes", vma->vm_start, vma->vm_flags);
	return 1;
}
