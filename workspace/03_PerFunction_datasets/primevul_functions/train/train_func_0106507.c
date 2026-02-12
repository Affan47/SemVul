void flush_thread(void)
{
#ifdef CONFIG_HAVE_HW_BREAKPOINT
	flush_ptrace_hw_breakpoint(current);
#else
	set_debug_reg_defaults(&current->thread);
#endif
}
