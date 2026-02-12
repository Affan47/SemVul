void arch_exit_mmap(struct mm_struct *mm)
{
	destroy_pagetable_cache(mm);

	if (radix_enabled()) {


		process_tb[mm->context.id].prtb0 = 0;
	}
}
