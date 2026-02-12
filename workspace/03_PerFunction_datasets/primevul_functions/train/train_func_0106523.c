bool ppc_breakpoint_available(void)
{
	if (dawr_enabled())
		return true;
	if (cpu_has_feature(CPU_FTR_ARCH_207S))
		return false;

	return true;
}
