setup_perf_event (void)
{
	int i, count = 0;
	mmap_mask = num_pages * getpagesize () - 1;
	num_perf = mono_cpu_count ();
	perf_data = calloc (num_perf, sizeof (PerfData));
	for (i = 0; i < num_perf; ++i) {
		count += setup_perf_event_for_cpu (perf_data + i, i);
	}
	if (count)
		return 1;
	free (perf_data);
	perf_data = NULL;
	return 0;
}
