log_timming (GGTimingInfo *info)
{

	int num_major_sections = major_collector.get_num_major_sections ();
	char full_timing_buff [1024];
	full_timing_buff [0] = '\0';

	if (!info->is_overflow)
	        sprintf (full_timing_buff, "total %.2fms, bridge %.2fms", info->stw_time / 1000.0f, (int)info->bridge_time / 1000.0f);
	if (info->generation == GENERATION_OLD)
	        mono_trace (G_LOG_LEVEL_INFO, MONO_TRACE_GC, "GC_MAJOR%s: (%s) pause %.2fms, %s major %dK/%dK los %dK/%dK",
	                info->is_overflow ? "_OVERFLOW" : "",
	                info->reason ? info->reason : "",
	                (int)info->total_time / 1000.0f,
	                full_timing_buff,
	                major_collector.section_size * num_major_sections / 1024,
	                major_collector.section_size * last_major_num_sections / 1024,
	                los_memory_usage / 1024,
	                last_los_memory_usage / 1024);
	else
	        mono_trace (G_LOG_LEVEL_INFO, MONO_TRACE_GC, "GC_MINOR%s: (%s) pause %.2fms, %s promoted %dK major %dK los %dK",
	        		info->is_overflow ? "_OVERFLOW" : "",
	                info->reason ? info->reason : "",
	                (int)info->total_time / 1000.0f,
	                full_timing_buff,
	                (num_major_sections - last_major_num_sections) * major_collector.section_size / 1024,
	                major_collector.section_size * num_major_sections / 1024,
	                los_memory_usage / 1024);
}
