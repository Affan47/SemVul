static void cpu_detect_tlb_amd(struct cpuinfo_x86 *c)
{
	u32 ebx, eax, ecx, edx;
	u16 mask = 0xfff;

	if (c->x86 < 0xf)
		return;

	if (c->extended_cpuid_level < 0x80000006)
		return;

	cpuid(0x80000006, &eax, &ebx, &ecx, &edx);

	tlb_lld_4k[ENTRIES] = (ebx >> 16) & mask;
	tlb_lli_4k[ENTRIES] = ebx & mask;


	if (c->x86 == 0xf) {
		cpuid(0x80000005, &eax, &ebx, &ecx, &edx);
		mask = 0xff;
	}


	if (!((eax >> 16) & mask)) {
		u32 a, b, c, d;

		cpuid(0x80000005, &a, &b, &c, &d);
		tlb_lld_2m[ENTRIES] = (a >> 16) & 0xff;
	} else {
		tlb_lld_2m[ENTRIES] = (eax >> 16) & mask;
	}


	tlb_lld_4m[ENTRIES] = tlb_lld_2m[ENTRIES] >> 1;


	if (!(eax & mask)) {

		if (c->x86 == 0x15 && c->x86_model <= 0x1f) {
			tlb_lli_2m[ENTRIES] = 1024;
		} else {
			cpuid(0x80000005, &eax, &ebx, &ecx, &edx);
			tlb_lli_2m[ENTRIES] = eax & 0xff;
		}
	} else
		tlb_lli_2m[ENTRIES] = eax & mask;

	tlb_lli_4m[ENTRIES] = tlb_lli_2m[ENTRIES] >> 1;

	cpu_set_tlb_flushall_shift(c);
}
