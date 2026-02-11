cpufreq_p4_get_frequency(struct cpuinfo_x86 *c)
{
	if (c->x86 == 0x06) {
		if (cpu_has(c, X86_FEATURE_EST))
			printk_once(KERN_WARNING PFX "Warning: EST-capable "
			       "CPU detected. The acpi-cpufreq module offers "
			       "voltage scaling in addition to frequency "
			       "scaling. You should use that instead of "
			       "p4-clockmod, if possible.\n");
		switch (c->x86_model) {
		case 0x0E:
		case 0x0F:
		case 0x16:
		case 0x1C:
			p4clockmod_driver.flags |= CPUFREQ_CONST_LOOPS;
			return speedstep_get_frequency(SPEEDSTEP_CPU_PCORE);
		case 0x0D:
			p4clockmod_driver.flags |= CPUFREQ_CONST_LOOPS;

		case 0x09:
			return speedstep_get_frequency(SPEEDSTEP_CPU_PM);
		}
	}

	if (c->x86 != 0xF)
		return 0;


	p4clockmod_driver.flags |= CPUFREQ_CONST_LOOPS;

	if (speedstep_detect_processor() == SPEEDSTEP_CPU_P4M) {
		printk(KERN_WARNING PFX "Warning: Pentium 4-M detected. "
		       "The speedstep-ich or acpi cpufreq modules offer "
		       "voltage scaling in addition of frequency scaling. "
		       "You should use either one instead of p4-clockmod, "
		       "if possible.\n");
		return speedstep_get_frequency(SPEEDSTEP_CPU_P4M);
	}

	return speedstep_get_frequency(SPEEDSTEP_CPU_P4D);
}
