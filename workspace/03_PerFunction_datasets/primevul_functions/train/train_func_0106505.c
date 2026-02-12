void __set_breakpoint(struct arch_hw_breakpoint *brk)
{
	memcpy(this_cpu_ptr(&current_brk), brk, sizeof(*brk));

	if (dawr_enabled())

		set_dawr(brk);
	else if (!cpu_has_feature(CPU_FTR_ARCH_207S))

		set_dabr(brk);
	else

		WARN_ON_ONCE(1);
}
