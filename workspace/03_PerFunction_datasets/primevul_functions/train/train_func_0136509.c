static int perf_get_aux_event(struct perf_event *event,
			      struct perf_event *group_leader)
{


	if (!group_leader)
		return 0;


	if (event->attr.aux_output && event->attr.aux_sample_size)
		return 0;

	if (event->attr.aux_output &&
	    !perf_aux_output_match(event, group_leader))
		return 0;

	if (event->attr.aux_sample_size && !group_leader->pmu->snapshot_aux)
		return 0;

	if (!atomic_long_inc_not_zero(&group_leader->refcount))
		return 0;


	event->aux_event = group_leader;

	return 1;
}
