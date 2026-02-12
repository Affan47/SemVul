static inline void load_mm_ldt(struct mm_struct *mm)
{
#ifdef CONFIG_MODIFY_LDT_SYSCALL
	struct ldt_struct *ldt;


	ldt = lockless_dereference(mm->context.ldt);


	if (unlikely(ldt))
		set_ldt(ldt->entries, ldt->nr_entries);
	else
		clear_LDT();
#else
	clear_LDT();
#endif
}
