static u64 precise_datala_hsw(struct perf_event *event, u64 status)
{
	union perf_mem_data_src dse;

	dse.val = PERF_MEM_NA;

	if (event->hw.flags & PERF_X86_EVENT_PEBS_ST_HSW)
		dse.mem_op = PERF_MEM_OP_STORE;
	else if (event->hw.flags & PERF_X86_EVENT_PEBS_LD_HSW)
		dse.mem_op = PERF_MEM_OP_LOAD;


	if (event->hw.flags & PERF_X86_EVENT_PEBS_ST_HSW) {
		if (status & 1)
			dse.mem_lvl = PERF_MEM_LVL_L1 | PERF_MEM_LVL_HIT;
		else
			dse.mem_lvl = PERF_MEM_LVL_L1 | PERF_MEM_LVL_MISS;
	}
	return dse.val;
}
