static void power_pmu_bhrb_read(struct perf_event *event, struct cpu_hw_events *cpuhw)
{
	u64 val;
	u64 addr;
	int r_index, u_index, pred;

	r_index = 0;
	u_index = 0;
	while (r_index < ppmu->bhrb_nr) {

		val = read_bhrb(r_index++);
		if (!val)

			break;
		else {
			addr = val & BHRB_EA;
			pred = val & BHRB_PREDICTION;

			if (!addr)

				continue;


			if (!(ppmu->flags & PPMU_ARCH_31) &&
			    is_kernel_addr(addr) && event->attr.exclude_kernel)
				continue;


			if (val & BHRB_TARGET) {


				cpuhw->bhrb_entries[u_index].to = addr;
				cpuhw->bhrb_entries[u_index].mispred = pred;
				cpuhw->bhrb_entries[u_index].predicted = ~pred;


				val = read_bhrb(r_index++);
				addr = val & BHRB_EA;
				if (val & BHRB_TARGET) {


					r_index--;
					addr = 0;
				}
				cpuhw->bhrb_entries[u_index].from = addr;
			} else {


				cpuhw->bhrb_entries[u_index].from = addr;
				cpuhw->bhrb_entries[u_index].to =
					power_pmu_bhrb_to(addr);
				cpuhw->bhrb_entries[u_index].mispred = pred;
				cpuhw->bhrb_entries[u_index].predicted = ~pred;
			}
			u_index++;

		}
	}
	cpuhw->bhrb_stack.nr = u_index;
	cpuhw->bhrb_stack.hw_idx = -1ULL;
	return;
}
