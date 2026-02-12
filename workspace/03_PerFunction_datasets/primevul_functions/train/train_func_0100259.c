void arch_unmap_area_topdown(struct mm_struct *mm, unsigned long addr)
{


	if (addr > mm->free_area_cache)
		mm->free_area_cache = addr;


	if (mm->free_area_cache > mm->mmap_base)
		mm->free_area_cache = mm->mmap_base;
}
