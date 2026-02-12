static bool is_ebb_event(struct perf_event *event)
{


	return (ppmu->flags & PPMU_ARCH_207S) &&
	       ((event->attr.config >> PERF_EVENT_CONFIG_EBB_SHIFT) & 1);
}
