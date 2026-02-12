void arch_unmap_area(struct mm_struct *mm, unsigned long addr)
{


	if (addr >= TASK_UNMAPPED_BASE && addr < mm->free_area_cache) {
		mm->free_area_cache = addr;
		mm->cached_hole_size = ~0UL;
	}
}
