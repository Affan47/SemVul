cvt_gate_to_trap(int vector, const gate_desc *val,
			    struct trap_info *info)
{
	unsigned long addr;

	if (val->type != GATE_TRAP && val->type != GATE_INTERRUPT)
		return 0;

	info->vector = vector;

	addr = gate_offset(*val);
#ifdef CONFIG_X86_64


	if (addr == (unsigned long)debug)
		addr = (unsigned long)xen_debug;
	else if (addr == (unsigned long)int3)
		addr = (unsigned long)xen_int3;
	else if (addr == (unsigned long)stack_segment)
		addr = (unsigned long)xen_stack_segment;
	else if (addr == (unsigned long)double_fault) {

		return 0;
#ifdef CONFIG_X86_MCE
	} else if (addr == (unsigned long)machine_check) {


		;
#endif
	} else if (addr == (unsigned long)nmi)


		;
	else {

		if (WARN_ON(val->ist != 0))
			return 0;
	}
#endif
	info->address = addr;

	info->cs = gate_segment(*val);
	info->flags = val->dpl;

	if (val->type == GATE_INTERRUPT)
		info->flags |= 1 << 2;

	return 1;
}
