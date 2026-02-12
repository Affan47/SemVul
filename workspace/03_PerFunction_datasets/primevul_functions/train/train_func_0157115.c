static int __mcheck_cpu_apply_quirks(struct cpuinfo_x86 *c)
{
	struct mca_config *cfg = &mca_cfg;

	if (c->x86_vendor == X86_VENDOR_UNKNOWN) {
		pr_info("unknown CPU type - not enabling MCE support\n");
		return -EOPNOTSUPP;
	}


	if (c->x86_vendor == X86_VENDOR_AMD) {
		if (c->x86 == 15 && cfg->banks > 4) {


			clear_bit(10, (unsigned long *)&mce_banks[4].ctl);
		}
		if (c->x86 < 0x11 && cfg->bootlog < 0) {


			cfg->bootlog = 0;
		}


		if (c->x86 == 6 && cfg->banks > 0)
			mce_banks[0].ctl = 0;


		if (c->x86 == 0x15 && c->x86_model <= 0xf)
			mce_flags.overflow_recov = 1;


		if (c->x86 == 0x15 &&
		    (c->x86_model >= 0x10 && c->x86_model <= 0x1f)) {
			int i;
			u64 hwcr;
			bool need_toggle;
			u32 msrs[] = {
				0x00000413,
				0xc0000408,
			};

			rdmsrl(MSR_K7_HWCR, hwcr);


			need_toggle = !(hwcr & BIT(18));

			if (need_toggle)
				wrmsrl(MSR_K7_HWCR, hwcr | BIT(18));


			for (i = 0; i < ARRAY_SIZE(msrs); i++)
				msr_clear_bit(msrs[i], 62);


			if (need_toggle)
				wrmsrl(MSR_K7_HWCR, hwcr);
		}
	}

	if (c->x86_vendor == X86_VENDOR_INTEL) {


		if (c->x86 == 6 && c->x86_model < 0x1A && cfg->banks > 0)
			mce_banks[0].init = 0;


		if ((c->x86 > 6 || (c->x86 == 6 && c->x86_model >= 0xe)) &&
			cfg->monarch_timeout < 0)
			cfg->monarch_timeout = USEC_PER_SEC;


		if (c->x86 == 6 && c->x86_model <= 13 && cfg->bootlog < 0)
			cfg->bootlog = 0;

		if (c->x86 == 6 && c->x86_model == 45)
			quirk_no_way_out = quirk_sandybridge_ifu;
	}
	if (cfg->monarch_timeout < 0)
		cfg->monarch_timeout = 0;
	if (cfg->bootlog != 0)
		cfg->panic_timeout = 30;

	return 0;
}
