static void svm_set_supported_cpuid(u32 func, struct kvm_cpuid_entry2 *entry)
{
	switch (func) {
	case 0x1:
		if (avic)
			entry->ecx &= ~F(X2APIC);
		break;
	case 0x80000001:
		if (nested)
			entry->ecx |= (1 << 2);
		break;
	case 0x80000008:
		if (boot_cpu_has(X86_FEATURE_LS_CFG_SSBD) ||
		     boot_cpu_has(X86_FEATURE_AMD_SSBD))
			entry->ebx |= F(VIRT_SSBD);
		break;
	case 0x8000000A:
		entry->eax = 1;
		entry->ebx = 8;

		entry->ecx = 0;
		entry->edx = 0;


		if (boot_cpu_has(X86_FEATURE_NRIPS))
			entry->edx |= F(NRIPS);


		if (npt_enabled)
			entry->edx |= F(NPT);

	}
}
