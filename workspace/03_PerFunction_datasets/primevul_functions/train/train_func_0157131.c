void mcheck_cpu_clear(struct cpuinfo_x86 *c)
{
	if (mca_cfg.disabled)
		return;

	if (!mce_available(c))
		return;


	__mcheck_cpu_clear_vendor(c);

}
