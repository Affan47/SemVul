load_separate_debug_info (const char *            main_filename,
			  struct dwarf_section *  xlink,
			  parse_func_type         parse_func,
			  check_func_type         check_func,
			  void *                  func_data,
                          void *                  file ATTRIBUTE_UNUSED)
{
  const char *   separate_filename;
  char *         debug_filename;
  char *         canon_dir;
  size_t         canon_dirlen;
  size_t         dirlen;
  char *         canon_filename;
  char *         canon_debug_filename;
  bool		 self;

  if ((separate_filename = parse_func (xlink, func_data)) == NULL)
    {
      warn (_("Corrupt debuglink section: %s\n"),
	    xlink->name ? xlink->name : xlink->uncompressed_name);
      return NULL;
    }


  canon_filename = lrealpath (main_filename);
  canon_dir = xstrdup (canon_filename);

  for (canon_dirlen = strlen (canon_dir); canon_dirlen > 0; canon_dirlen--)
    if (IS_DIR_SEPARATOR (canon_dir[canon_dirlen - 1]))
      break;
  canon_dir[canon_dirlen] = '\0';

#ifndef DEBUGDIR
#define DEBUGDIR "/lib/debug"
#endif
#ifndef EXTRA_DEBUG_ROOT1
#define EXTRA_DEBUG_ROOT1 "/usr/lib/debug"
#endif
#ifndef EXTRA_DEBUG_ROOT2
#define EXTRA_DEBUG_ROOT2 "/usr/lib/debug/usr"
#endif

  debug_filename = (char *) malloc (strlen (DEBUGDIR) + 1
				    + canon_dirlen
				    + strlen (".debug/")
#ifdef EXTRA_DEBUG_ROOT1
				    + strlen (EXTRA_DEBUG_ROOT1)
#endif
#ifdef EXTRA_DEBUG_ROOT2
				    + strlen (EXTRA_DEBUG_ROOT2)
#endif
				    + strlen (separate_filename)
				    + 1);
  if (debug_filename == NULL)
    {
      warn (_("Out of memory"));
      free (canon_dir);
      free (canon_filename);
      return NULL;
    }


  sprintf (debug_filename, "%s", separate_filename);
  if (check_func (debug_filename, func_data))
    goto found;


  sprintf (debug_filename, ".debug/%s", separate_filename);
  if (check_func (debug_filename, func_data))
    goto found;


  sprintf (debug_filename, "%s%s", canon_dir, separate_filename);
  if (check_func (debug_filename, func_data))
    goto found;


  sprintf (debug_filename, "%s.debug/%s", canon_dir, separate_filename);
  if (check_func (debug_filename, func_data))
    goto found;

#ifdef EXTRA_DEBUG_ROOT1

  sprintf (debug_filename, "%s/%s", EXTRA_DEBUG_ROOT1, separate_filename);
  if (check_func (debug_filename, func_data))
    goto found;


  sprintf (debug_filename, "%s/%s/%s", EXTRA_DEBUG_ROOT1, canon_dir, separate_filename);
  if (check_func (debug_filename, func_data))
    goto found;
#endif

#ifdef EXTRA_DEBUG_ROOT2

  sprintf (debug_filename, "%s/%s", EXTRA_DEBUG_ROOT2, separate_filename);
  if (check_func (debug_filename, func_data))
    goto found;
#endif


  strcpy (debug_filename, DEBUGDIR);
  dirlen = strlen (DEBUGDIR) - 1;
  if (dirlen > 0 && DEBUGDIR[dirlen] != '/')
    strcat (debug_filename, "/");
  strcat (debug_filename, (const char *) separate_filename);

  if (check_func (debug_filename, func_data))
    goto found;

#if HAVE_LIBDEBUGINFOD
  {
    char * tmp_filename;

    if (use_debuginfod
	&& debuginfod_fetch_separate_debug_info (xlink,
						 & tmp_filename,
						 file))
      {


        free (debug_filename);
        debug_filename = tmp_filename;
        goto found;
      }
  }
#endif

  if (do_debug_links)
    {

      warn (_("could not find separate debug file '%s'\n"),
	    separate_filename);
      warn (_("tried: %s\n"), debug_filename);

#ifdef EXTRA_DEBUG_ROOT2
      sprintf (debug_filename, "%s/%s", EXTRA_DEBUG_ROOT2,
	       separate_filename);
      warn (_("tried: %s\n"), debug_filename);
#endif

#ifdef EXTRA_DEBUG_ROOT1
      sprintf (debug_filename, "%s/%s/%s", EXTRA_DEBUG_ROOT1,
	       canon_dir, separate_filename);
      warn (_("tried: %s\n"), debug_filename);

      sprintf (debug_filename, "%s/%s", EXTRA_DEBUG_ROOT1,
	       separate_filename);
      warn (_("tried: %s\n"), debug_filename);
#endif

      sprintf (debug_filename, "%s.debug/%s", canon_dir,
	       separate_filename);
      warn (_("tried: %s\n"), debug_filename);

      sprintf (debug_filename, "%s%s", canon_dir, separate_filename);
      warn (_("tried: %s\n"), debug_filename);

      sprintf (debug_filename, ".debug/%s", separate_filename);
      warn (_("tried: %s\n"), debug_filename);

      sprintf (debug_filename, "%s", separate_filename);
      warn (_("tried: %s\n"), debug_filename);

#if HAVE_LIBDEBUGINFOD
      if (use_debuginfod)
	{
	  char *urls = getenv (DEBUGINFOD_URLS_ENV_VAR);

	  if (urls == NULL)
	    urls = "";

	  warn (_("tried: DEBUGINFOD_URLS=%s\n"), urls);
	}
#endif
    }

  free (canon_dir);
  free (debug_filename);
  free (canon_filename);
  return NULL;

 found:
  free (canon_dir);

  canon_debug_filename = lrealpath (debug_filename);
  self = strcmp (canon_debug_filename, canon_filename) == 0;
  free (canon_filename);
  free (canon_debug_filename);
  if (self)
    {
      free (debug_filename);
      return NULL;
    }

  void * debug_handle;


  if ((debug_handle = open_debug_file (debug_filename)) == NULL)
    {
      warn (_("failed to open separate debug file: %s\n"), debug_filename);
      free (debug_filename);
      return NULL;
    }


  if (do_debug_links)
    printf (_("\n%s: Found separate debug info file: %s\n"), main_filename, debug_filename);
  add_separate_debug_file (debug_filename, debug_handle);


  return debug_handle;
}
