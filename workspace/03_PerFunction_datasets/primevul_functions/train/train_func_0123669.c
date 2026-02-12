static void init_amd(struct cpuinfo_x86 *c)
{
	u32 dummy;
	unsigned long long value;

#ifdef CONFIG_SMP


	if (c->x86 == 0xf) {
		rdmsrl(MSR_K7_HWCR, value);
		value |= 1 << 6;
		wrmsrl(MSR_K7_HWCR, value);
	}
#endif

	early_init_amd(c);


	clear_cpu_cap(c, 0*32+31);

#ifdef CONFIG_X86_64

	if (c->x86 == 0xf) {
		u32 level;

		level = cpuid_eax(1);
		if ((level >= 0x0f48 && level < 0x0f50) || level >= 0x0f58)
			set_cpu_cap(c, X86_FEATURE_REP_GOOD);


		if (c->x86_model < 0x14 && cpu_has(c, X86_FEATURE_LAHF_LM)) {
			clear_cpu_cap(c, X86_FEATURE_LAHF_LM);
			if (!rdmsrl_amd_safe(0xc001100d, &value)) {
				value &= ~(1ULL << 32);
				wrmsrl_amd_safe(0xc001100d, value);
			}
		}

	}
	if (c->x86 >= 0x10)
		set_cpu_cap(c, X86_FEATURE_REP_GOOD);


	c->apicid = hard_smp_processor_id();
#else


	switch (c->x86) {
	case 4:
		init_amd_k5(c);
		break;
	case 5:
		init_amd_k6(c);
		break;
	case 6:
		init_amd_k7(c);
		break;
	}


	if (c->x86 < 6)
		clear_cpu_cap(c, X86_FEATURE_MCE);
#endif


	if (c->x86 >= 6)
		set_cpu_cap(c, X86_FEATURE_FXSAVE_LEAK);

	if (!c->x86_model_id[0]) {
		switch (c->x86) {
		case 0xf:


			strcpy(c->x86_model_id, "Hammer");
			break;
		}
	}


	if ((c->x86 == 0x15) &&
	    (c->x86_model >= 0x10) && (c->x86_model <= 0x1f) &&
	    !cpu_has(c, X86_FEATURE_TOPOEXT)) {

		if (!rdmsrl_safe(0xc0011005, &value)) {
			value |= 1ULL << 54;
			wrmsrl_safe(0xc0011005, value);
			rdmsrl(0xc0011005, value);
			if (value & (1ULL << 54)) {
				set_cpu_cap(c, X86_FEATURE_TOPOEXT);
				printk(KERN_INFO FW_INFO "CPU: Re-enabling "
				  "disabled Topology Extensions Support\n");
			}
		}
	}


	if ((c->x86 == 0x15) &&
	    (c->x86_model >= 0x02) && (c->x86_model < 0x20)) {

		if (!rdmsrl_safe(0xc0011021, &value) && !(value & 0x1E)) {
			value |= 0x1E;
			wrmsrl_safe(0xc0011021, value);
		}
	}

	cpu_detect_cache_sizes(c);


	if (c->extended_cpuid_level >= 0x80000008) {
		amd_detect_cmp(c);
		srat_detect_node(c);
	}

#ifdef CONFIG_X86_32
	detect_ht(c);
#endif

	init_amd_cacheinfo(c);

	if (c->x86 >= 0xf)
		set_cpu_cap(c, X86_FEATURE_K8);

	if (cpu_has_xmm2) {

		set_cpu_cap(c, X86_FEATURE_MFENCE_RDTSC);
	}

#ifdef CONFIG_X86_64
	if (c->x86 == 0x10) {

		if (c == &boot_cpu_data)
			check_enable_amd_mmconf_dmi();

		fam10h_check_enable_mmcfg();
	}

	if (c == &boot_cpu_data && c->x86 >= 0xf) {
		unsigned long long tseg;


		if (!rdmsrl_safe(MSR_K8_TSEG_ADDR, &tseg)) {
			unsigned long pfn = tseg >> PAGE_SHIFT;

			printk(KERN_DEBUG "tseg: %010llx\n", tseg);
			if (pfn_range_is_mapped(pfn, pfn + 1))
				set_memory_4k((unsigned long)__va(tseg), 1);
		}
	}
#endif


	if (c->x86 > 0x11)
		set_cpu_cap(c, X86_FEATURE_ARAT);

	if (c->x86 == 0x10) {


		u64 mask;
		int err;

		err = rdmsrl_safe(MSR_AMD64_MCx_MASK(4), &mask);
		if (err == 0) {
			mask |= (1 << 10);
			wrmsrl_safe(MSR_AMD64_MCx_MASK(4), mask);
		}


		rdmsrl_safe(MSR_AMD64_BU_CFG2, &value);
		value &= ~(1ULL << 24);
		wrmsrl_safe(MSR_AMD64_BU_CFG2, value);

		if (cpu_has_amd_erratum(c, amd_erratum_383))
			set_cpu_bug(c, X86_BUG_AMD_TLB_MMATCH);
	}

	if (cpu_has_amd_erratum(c, amd_erratum_400))
		set_cpu_bug(c, X86_BUG_AMD_APIC_C1E);

	rdmsr_safe(MSR_AMD64_PATCH_LEVEL, &c->microcode, &dummy);
}
