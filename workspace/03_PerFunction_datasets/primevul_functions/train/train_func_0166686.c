try_dlopen (lt_dlhandle *phandle, const char *filename, const char *ext,
	    lt_dladvise advise)
{
  const char *	saved_error	= 0;
  char *	archive_name	= 0;
  char *	canonical	= 0;
  char *	base_name	= 0;
  char *	dir		= 0;
  char *	name		= 0;
  char *        attempt		= 0;
  int		errors		= 0;
  lt_dlhandle	newhandle;

  assert (phandle);
  assert (*phandle == 0);

#ifdef LT_DEBUG_LOADERS
  fprintf (stderr, "try_dlopen (%s, %s)\n",
	   filename ? filename : "(null)",
	   ext ? ext : "(null)");
#endif

  LT__GETERROR (saved_error);


  if (!filename)
    {
      *phandle = (lt_dlhandle) lt__zalloc (sizeof (struct lt__handle));
      if (*phandle == 0)
	return 1;

      newhandle	= *phandle;


      newhandle->info.is_resident = 1;

      if (tryall_dlopen (&newhandle, 0, advise, 0) != 0)
	{
	  FREE (*phandle);
	  return 1;
	}

      goto register_handle;
    }

  assert (filename && *filename);

  if (ext)
    {
      attempt = MALLOC (char, LT_STRLEN (filename) + LT_STRLEN (ext) + 1);
      if (!attempt)
	return 1;

      sprintf(attempt, "%s%s", filename, ext);
    }
  else
    {
      attempt = lt__strdup (filename);
      if (!attempt)
	return 1;
    }


  if (canonicalize_path (attempt, &canonical) != 0)
    {
      ++errors;
      goto cleanup;
    }


  base_name = strrchr (canonical, '/');
  if (base_name)
    {
      size_t dirlen = (1+ base_name) - canonical;

      dir = MALLOC (char, 1+ dirlen);
      if (!dir)
	{
	  ++errors;
	  goto cleanup;
	}

      strncpy (dir, canonical, dirlen);
      dir[dirlen] = LT_EOS_CHAR;

      ++base_name;
    }
  else
    MEMREASSIGN (base_name, canonical);

  assert (base_name && *base_name);

  ext = strrchr (base_name, '.');
  if (!ext)
    {
      ext = base_name + LT_STRLEN (base_name);
    }


  name = MALLOC (char, ext - base_name + 1);
  if (!name)
    {
      ++errors;
      goto cleanup;
    }


  {
    int i;
    for (i = 0; i < ext - base_name; ++i)
      {
	if (isalnum ((unsigned char)(base_name[i])))
	  {
	    name[i] = base_name[i];
	  }
	else
	  {
	    name[i] = '_';
	  }
      }
    name[ext - base_name] = LT_EOS_CHAR;
  }


  if (!dir)
    {
      const lt_dlvtable *vtable	= lt_dlloader_find ("lt_preopen");

      if (vtable)
	{

	  archive_name = MALLOC (char, LT_STRLEN (name) + strlen (libext) + 2);
	  *phandle = (lt_dlhandle) lt__zalloc (sizeof (struct lt__handle));

	  if ((*phandle == NULL) || (archive_name == NULL))
	    {
	      ++errors;
	      goto cleanup;
	    }
	  newhandle = *phandle;


	  sprintf (archive_name, "%s.%s", name, libext);

	  if (tryall_dlopen (&newhandle, archive_name, advise, vtable) == 0)
	    {
	      goto register_handle;
	    }


	  FREE (*phandle);
	  newhandle = NULL;
	}
    }


  if (advise && advise->try_preload_only)
    {
      goto cleanup;
    }


  if (ext && streq (ext, archive_ext))
    {

      FILE *	file	 = 0;
      char *	dlname	 = 0;
      char *	old_name = 0;
      char *	libdir	 = 0;
      char *	deplibs	 = 0;


      int	installed = 1;


      if (!dir)
	{
	  const char *search_path = user_search_path;

	  if (search_path)
	    file = find_file (user_search_path, base_name, &dir);

	  if (!file)
	    {
	      search_path = getenv (LTDL_SEARCHPATH_VAR);
	      if (search_path)
		file = find_file (search_path, base_name, &dir);
	    }

#if defined(LT_MODULE_PATH_VAR)
	  if (!file)
	    {
	      search_path = getenv (LT_MODULE_PATH_VAR);
	      if (search_path)
		file = find_file (search_path, base_name, &dir);
	    }
#endif
#if defined(LT_DLSEARCH_PATH)
	  if (!file && *sys_dlsearch_path)
	    {
	      file = find_file (sys_dlsearch_path, base_name, &dir);
	    }
#endif
	}
      else
	{
	  file = fopen (attempt, LT_READTEXT_MODE);
	}


      if (!file)
	{
	  LT__SETERROR (FILE_NOT_FOUND);
	  ++errors;
	  goto cleanup;
	}


      if (parse_dotla_file(file, &dlname, &libdir, &deplibs,
	    &old_name, &installed) != 0)
	++errors;

      fclose (file);


      *phandle = (lt_dlhandle) lt__zalloc (sizeof (struct lt__handle));
      if (*phandle == 0)
	++errors;

      if (errors)
	{
	  FREE (dlname);
	  FREE (old_name);
	  FREE (libdir);
	  FREE (deplibs);
	  FREE (*phandle);
	  goto cleanup;
	}

      assert (*phandle);

      if (load_deplibs (*phandle, deplibs) == 0)
	{
	  newhandle = *phandle;

	  if (find_module (&newhandle, dir, libdir, dlname, old_name,
			   installed, advise))
	    {
	      unload_deplibs (*phandle);
	      ++errors;
	    }
	}
      else
	{
	  ++errors;
	}

      FREE (dlname);
      FREE (old_name);
      FREE (libdir);
      FREE (deplibs);

      if (errors)
	{
	  FREE (*phandle);
	  goto cleanup;
	}

      if (*phandle != newhandle)
	{
	  unload_deplibs (*phandle);
	}
    }
  else
    {

      *phandle = (lt_dlhandle) lt__zalloc (sizeof (struct lt__handle));
      if (*phandle == 0)
	{
	  ++errors;
	  goto cleanup;
	}

      newhandle = *phandle;


      if ((dir || (!find_handle (user_search_path, base_name,
				 &newhandle, advise)
		   && !find_handle (getenv (LTDL_SEARCHPATH_VAR), base_name,
				    &newhandle, advise)
#if defined(LT_MODULE_PATH_VAR)
		   && !find_handle (getenv (LT_MODULE_PATH_VAR), base_name,
				    &newhandle, advise)
#endif
#if defined(LT_DLSEARCH_PATH)
		   && !find_handle (sys_dlsearch_path, base_name,
				    &newhandle, advise)
#endif
		   )))
	{
	  if (tryall_dlopen (&newhandle, attempt, advise, 0) != 0)
	    {
	      newhandle = NULL;
	    }
	}

      if (!newhandle)
	{
	  FREE (*phandle);
	  ++errors;
	  goto cleanup;
	}
    }

 register_handle:
  MEMREASSIGN (*phandle, newhandle);

  if ((*phandle)->info.ref_count == 0)
    {
      (*phandle)->info.ref_count	= 1;
      MEMREASSIGN ((*phandle)->info.name, name);

      (*phandle)->next	= handles;
      handles		= *phandle;
    }

  LT__SETERRORSTR (saved_error);

 cleanup:
  FREE (dir);
  FREE (attempt);
  FREE (name);
  if (!canonical)
    FREE (base_name);
  FREE (canonical);
  FREE (archive_name);

  return errors;
}
