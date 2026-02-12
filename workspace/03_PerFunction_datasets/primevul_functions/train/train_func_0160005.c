static u64 load_latency_data(u64 status)
{
	union intel_x86_pebs_dse dse;
	u64 val;

	dse.val = status;


	val = pebs_data_source[dse.ld_dse];


	if (x86_pmu.pebs_no_tlb) {
		val |= P(TLB, NA) | P(LOCK, NA);
		return val;
	}


	if (dse.ld_stlb_miss)
		val |= P(TLB, MISS) | P(TLB, L2);
	else
		val |= P(TLB, HIT) | P(TLB, L1) | P(TLB, L2);


	if (dse.ld_locked)
		val |= P(LOCK, LOCKED);


	if (!x86_pmu.pebs_block) {
		val |= P(BLK, NA);
		return val;
	}


	if (dse.ld_data_blk)
		val |= P(BLK, DATA);


	if (dse.ld_addr_blk)
		val |= P(BLK, ADDR);

	if (!dse.ld_data_blk && !dse.ld_addr_blk)
		val |= P(BLK, NA);

	return val;
}
