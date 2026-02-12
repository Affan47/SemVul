load_separate_debug_files (void * file, const char * filename)
{

  if (! do_follow_links && ! do_debug_links)
    return false;


  if (load_debug_section (str, file)
      && load_debug_section (abbrev, file)
      && load_debug_section (info, file))
    {

      load_debug_section (debug_addr, file);

      load_debug_section (str_index, file);

      free_dwo_info ();

      if (process_debug_info (& debug_displays[info].section, file, abbrev,
			      true, false))
	{
	  bool introduced = false;
	  dwo_info *dwinfo;
	  const char *dir = NULL;
	  const char *id = NULL;
	  const char *name = NULL;

	  for (dwinfo = first_dwo_info; dwinfo != NULL; dwinfo = dwinfo->next)
	    {

	      switch (dwinfo->type)
		{
		case DWO_NAME:
		  if (name != NULL)
		    warn (_("Multiple DWO_NAMEs encountered for the same CU\n"));
		  name = dwinfo->value;
		  break;

		case DWO_DIR:


		  dir = dwinfo->value;
		  break;

		case DWO_ID:
		  if (id != NULL)
		    warn (_("multiple DWO_IDs encountered for the same CU\n"));
		  id = dwinfo->value;
		  break;

		default:
		  error (_("Unexpected DWO INFO type"));
		  break;
		}


	      if (name != NULL
		  && (dwinfo->next == NULL
		      || dwinfo->next->cu_offset != dwinfo->cu_offset))
		{
		  if (do_debug_links)
		    {
		      if (! introduced)
			{
			  printf (_("The %s section contains link(s) to dwo file(s):\n\n"),
				  debug_displays [info].section.uncompressed_name);
			  introduced = true;
			}

		      printf (_("  Name:      %s\n"), name);
		      printf (_("  Directory: %s\n"), dir ? dir : _("<not-found>"));
		      if (id != NULL)
			display_data (printf (_("  ID:       ")), (unsigned char *) id, 8);
		      else
			printf (_("  ID:        <not specified>\n"));
		      printf ("\n\n");
		    }

		  if (do_follow_links)
		    load_dwo_file (filename, name, dir, id);

		  name = dir = id = NULL;
		}
	    }
	}
    }

  if (! do_follow_links)


    return false;


  check_for_and_load_links (file, filename);
  if (first_separate_info != NULL)
    return true;

  do_follow_links = 0;
  return false;
}
