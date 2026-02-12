load_debug_info (void * file)
{


  if (num_debug_info_entries == DEBUG_INFO_UNAVAILABLE)
    return 0;


  if (num_debug_info_entries > 0)
    return num_debug_info_entries;


  (void) load_cu_tu_indexes (file);

  if (load_debug_section_with_follow (info, file)
      && process_debug_info (&debug_displays [info].section, file, abbrev, true, false))
    return num_debug_info_entries;

  if (load_debug_section_with_follow (info_dwo, file)
      && process_debug_info (&debug_displays [info_dwo].section, file,
			     abbrev_dwo, true, false))
    return num_debug_info_entries;

  num_debug_info_entries = DEBUG_INFO_UNAVAILABLE;
  return 0;
}
