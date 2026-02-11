xen_cpuid(unsigned int *ax, unsigned int *bx,
		      unsigned int *cx, unsigned int *dx)
{
	unsigned maskebx = ~0;
	unsigned maskecx = ~0;
	unsigned maskedx = ~0;
	unsigned setecx = 0;


	switch (*ax) {
	case 1:
		maskecx = cpuid_leaf1_ecx_mask;
		setecx = cpuid_leaf1_ecx_set_mask;
		maskedx = cpuid_leaf1_edx_mask;
		break;

	case CPUID_MWAIT_LEAF:

		*ax = 0;
		*bx = 0;
		*cx = cpuid_leaf5_ecx_val;
		*dx = cpuid_leaf5_edx_val;
		return;

	case CPUID_THERM_POWER_LEAF:

		maskecx = ~(1 << APERFMPERF_PRESENT);
		break;

	case 0xb:

		maskebx = 0;
		break;
	}

	asm(XEN_EMULATE_PREFIX "cpuid"
		: "=a" (*ax),
		  "=b" (*bx),
		  "=c" (*cx),
		  "=d" (*dx)
		: "0" (*ax), "2" (*cx));

	*bx &= maskebx;
	*cx &= maskecx;
	*cx |= setecx;
	*dx &= maskedx;

}
