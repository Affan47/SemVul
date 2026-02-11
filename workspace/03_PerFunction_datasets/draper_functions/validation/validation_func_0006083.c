fe_file_change (const struct line_map *new_map)
{
  if (new_map == NULL)
    return;

  if (new_map->reason == LC_ENTER)
    {


      if (!MAIN_FILE_P (new_map))
	{
	  unsigned int included_at = LAST_SOURCE_LINE_LOCATION (new_map - 1);
	  int line = 0;
	  if (included_at > BUILTINS_LOCATION)
	    line = SOURCE_LINE (new_map - 1, included_at);

	  input_location = new_map->start_location;
	  (*debug_hooks->start_source_file) (line, LINEMAP_FILE (new_map));
#ifndef NO_IMPLICIT_EXTERN_C
	  if (c_header_level)
	    ++c_header_level;
	  else if (LINEMAP_SYSP (new_map) == 2)
	    {
	      c_header_level = 1;
	      ++pending_lang_change;
	    }
#endif
	}
    }
  else if (new_map->reason == LC_LEAVE)
    {
#ifndef NO_IMPLICIT_EXTERN_C
      if (c_header_level && --c_header_level == 0)
	{
	  if (LINEMAP_SYSP (new_map) == 2)
	    warning (0, "badly nested C headers from preprocessor");
	  --pending_lang_change;
	}
#endif
      input_location = new_map->start_location;

      (*debug_hooks->end_source_file) (LINEMAP_LINE (new_map));
    }

  update_header_times (LINEMAP_FILE (new_map));
  input_location = new_map->start_location;
}
