static inline void switch_ldt(struct mm_struct *prev, struct mm_struct *next)
{
#ifdef CONFIG_MODIFY_LDT_SYSCALL


	if (unlikely((unsigned long)prev->context.ldt |
		     (unsigned long)next->context.ldt))
		load_mm_ldt(next);
#endif

	DEBUG_LOCKS_WARN_ON(preemptible());
}
