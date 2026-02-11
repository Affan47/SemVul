load_latency_data(u64 status)
{
	union intel_x86_pebs_dse dse;
	u64 val;
	int model = boot_cpu_data.x86_model;
	int fam = boot_cpu_data.x86;

	dse.val = status;


	val = pebs_data_source[dse.ld_dse];


	if (fam == 0x6 && (model == 26 || model == 30
	    || model == 31 || model == 46)) {
		val |= P(TLB, NA) | P(LOCK, NA);
		return val;
	}


	if (dse.ld_stlb_miss)
		val |= P(TLB, MISS) | P(TLB, L2);
	else
		val |= P(TLB, HIT) | P(TLB, L1) | P(TLB, L2);


	if (dse.ld_locked)
		val |= P(LOCK, LOCKED);

	return val;
}
