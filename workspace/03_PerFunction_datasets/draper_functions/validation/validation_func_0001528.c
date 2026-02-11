fpu__init_system_early_generic(struct cpuinfo_x86 *c)
{
	unsigned long cr0;
	u16 fsw, fcw;

	fsw = fcw = 0xffff;

	cr0 = read_cr0();
	cr0 &= ~(X86_CR0_TS | X86_CR0_EM);
	write_cr0(cr0);

	asm volatile("fninit ; fnstsw %0 ; fnstcw %1"
		     : "+m" (fsw), "+m" (fcw));

	if (fsw == 0 && (fcw & 0x103f) == 0x003f)
		set_cpu_cap(c, X86_FEATURE_FPU);
	else
		clear_cpu_cap(c, X86_FEATURE_FPU);

#ifndef CONFIG_MATH_EMULATION
	if (!cpu_has_fpu) {
		pr_emerg("x86/fpu: Giving up, no FPU found and no math emulation present\n");
		for (;;)
			asm volatile("hlt");
	}
#endif
}
