static void ebb_event_add(struct perf_event *event)
{
	if (!is_ebb_event(event) || current->thread.used_ebb)
		return;


	current->thread.used_ebb = 1;
	current->thread.mmcr0 |= MMCR0_PMXE;
}
