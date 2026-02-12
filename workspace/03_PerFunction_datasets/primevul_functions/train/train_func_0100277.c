static int maydump(struct vm_area_struct *vma)
{

	if (vma->vm_flags & VM_ALWAYSDUMP)
		return 1;


	if (vma->vm_flags & (VM_IO | VM_RESERVED))
		return 0;


	if (vma->vm_flags & VM_SHARED)
		return vma->vm_file->f_path.dentry->d_inode->i_nlink == 0;


	if (!vma->anon_vma)
		return 0;

	return 1;
}
