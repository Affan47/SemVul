static bool regs_use_siar(struct pt_regs *regs)
{


	return ((TRAP(regs) == INTERRUPT_PERFMON) && regs->result);
}
