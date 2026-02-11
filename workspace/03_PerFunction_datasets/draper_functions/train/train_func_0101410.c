mono_profiler_install_allocation (MonoProfileAllocFunc callback)
{
	mono_gc_enable_alloc_events ();
	if (!prof_list)
		return;
	prof_list->allocation_cb = callback;
}
