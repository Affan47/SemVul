glob_filename (pathname, flags)
     char *pathname;
     int flags;
{
  char **result, **new_result;
  unsigned int result_size;
  char *directory_name, *filename, *dname, *fn;
  unsigned int directory_len;
  int free_dirname;
  int dflags, hasglob;

  result = (char **) malloc (sizeof (char *));
  result_size = 1;
  if (result == NULL)
    return (NULL);

  result[0] = NULL;

  directory_name = NULL;


  filename = strrchr (pathname, '/');
#if defined (EXTENDED_GLOB)
  if (filename && extended_glob)
    {
      fn = glob_dirscan (pathname, '/');
#if DEBUG_MATCHING
      if (fn != filename)
	fprintf (stderr, "glob_filename: glob_dirscan: fn (%s) != filename (%s)\n", fn ? fn : "(null)", filename);
#endif
      filename = fn;
    }
#endif

  if (filename == NULL)
    {
      filename = pathname;
      directory_name = "";
      directory_len = 0;
      free_dirname = 0;
    }
  else
    {
      directory_len = (filename - pathname) + 1;
      directory_name = (char *) malloc (directory_len + 1);

      if (directory_name == 0)
	{
	  free (result);
	  return (NULL);
	}

      bcopy (pathname, directory_name, directory_len);
      directory_name[directory_len] = '\0';
      ++filename;
      free_dirname = 1;
    }

  hasglob = 0;


  if (directory_len > 0 && (hasglob = glob_pattern_p (directory_name)) == 1)
    {
      char **directories, *d, *p;
      register unsigned int i;
      int all_starstar, last_starstar;

      all_starstar = last_starstar = 0;
      d = directory_name;
      dflags = flags & ~GX_MARKDIRS;


      if ((flags & GX_GLOBSTAR) && d[0] == '*' && d[1] == '*' && (d[2] == '/' || d[2] == '\0'))
	{
	  p = d;
	  while (d[0] == '*' && d[1] == '*' && (d[2] == '/' || d[2] == '\0'))
	    {
	      p = d;
	      if (d[2])
		{
		  d += 3;
		  while (*d == '/')
		    d++;
		  if (*d == 0)
		    break;
		}
	    }
	  if (*d == 0)
	    all_starstar = 1;
	  d = p;
	  dflags |= GX_ALLDIRS|GX_ADDCURDIR;
	  directory_len = strlen (d);
	}


      if ((flags & GX_GLOBSTAR) && all_starstar == 0)
	{
	  int dl, prev;
	  prev = dl = directory_len;
	  while (dl >= 4 && d[dl - 1] == '/' &&
			   d[dl - 2] == '*' &&
			   d[dl - 3] == '*' &&
			   d[dl - 4] == '/')
	    prev = dl, dl -= 3;
	  if (dl != directory_len)
	    last_starstar = 1;
	  directory_len = prev;
	}


      if (last_starstar && directory_len > 4 &&
	    filename[0] == '*' && filename[1] == '*' && filename[2] == 0)
	{
	  directory_len -= 3;
	}

      if (d[directory_len - 1] == '/')
	d[directory_len - 1] = '\0';

      directories = glob_filename (d, dflags|GX_RECURSE);

      if (free_dirname)
	{
	  free (directory_name);
	  directory_name = NULL;
	}

      if (directories == NULL)
	goto memory_error;
      else if (directories == (char **)&glob_error_return)
	{
	  free ((char *) result);
	  return ((char **) &glob_error_return);
	}
      else if (*directories == NULL)
	{
	  free ((char *) directories);
	  free ((char *) result);
	  return ((char **) &glob_error_return);
	}


      if (all_starstar && filename[0] == '*' && filename[1] == '*' && filename[2] == 0)
	{
	  free ((char *) directories);
	  free (directory_name);
	  directory_name = NULL;
	  directory_len = 0;
	  goto only_filename;
	}


      for (i = 0; directories[i] != NULL; ++i)
	{
	  char **temp_results;
	  int shouldbreak;

	  shouldbreak = 0;


	  dname = directories[i];
	  dflags = flags & ~(GX_MARKDIRS|GX_ALLDIRS|GX_ADDCURDIR);

	  if ((flags & GX_GLOBSTAR) && filename[0] == '*' && filename[1] == '*' && filename[2] == '\0')
	    dflags |= GX_ALLDIRS|GX_ADDCURDIR;
	  if (dname[0] == '\0' && filename[0])
	    {
	      dflags |= GX_NULLDIR;
	      dname = ".";
	    }


	  if (all_starstar && (dflags & GX_NULLDIR) == 0)
	    {
	      int dlen;


	      if (glob_testdir (dname, flags|GX_ALLDIRS) == -2 && glob_testdir (dname, 0) == 0)
		{
		  if (filename[0] != 0)
		    temp_results = (char **)&glob_error_return;
		  else
		    {

		      temp_results = (char **)malloc (2 * sizeof (char *));
		      if (temp_results == NULL)
			goto memory_error;
		      temp_results[0] = (char *)malloc (1);
		      if (temp_results[0] == 0)
			{
			  free (temp_results);
			  goto memory_error;
			}
		      **temp_results = '\0';
		      temp_results[1] = NULL;
		      dflags |= GX_SYMLINK;
		    }
		}
	      else
		temp_results = glob_vector (filename, dname, dflags);
	    }
	  else
	    temp_results = glob_vector (filename, dname, dflags);


	  if (temp_results == NULL)
	    goto memory_error;
	  else if (temp_results == (char **)&glob_error_return)

	    ;
	  else
	    {
	      char **array;
	      register unsigned int l;


	      if ((dflags & GX_ALLDIRS) && filename[0] == '*' && filename[1] == '*' && (filename[2] == '\0' || filename[2] == '/'))
		{


#define NULL_PLACEHOLDER(x)	((x) && *(x) && **(x) == 0)
		  if ((dflags & GX_NULLDIR) && (flags & GX_NULLDIR) == 0 &&
			NULL_PLACEHOLDER (temp_results))
#undef NULL_PLACEHOLDER
		    {
		      register int i, n;
		      for (n = 0; temp_results[n] && *temp_results[n] == 0; n++)
			;
		      i = n;
		      do
			temp_results[i - n] = temp_results[i];
		      while (temp_results[i++] != 0);
		      array = temp_results;
		      shouldbreak = 1;
		    }
	          else
		    array = temp_results;
		}
	      else if (dflags & GX_SYMLINK)
		array = glob_dir_to_array (directories[i], temp_results, flags);
	      else
		array = glob_dir_to_array (directories[i], temp_results, flags);
	      l = 0;
	      while (array[l] != NULL)
		++l;

	      new_result = (char **)realloc (result, (result_size + l) * sizeof (char *));

	      if (new_result == NULL)
		{
		  for (l = 0; array[l]; ++l)
		    free (array[l]);
		  free ((char *)array);
		  goto memory_error;
		}
	      result = new_result;

	      for (l = 0; array[l] != NULL; ++l)
		result[result_size++ - 1] = array[l];

	      result[result_size - 1] = NULL;


	      if (array != temp_results)
		free ((char *) array);
	      else if ((dflags & GX_ALLDIRS) && filename[0] == '*' && filename[1] == '*' && filename[2] == '\0')
		free (temp_results);

	      if (shouldbreak)
		break;
	    }
	}

      for (i = 0; directories[i]; i++)
	free (directories[i]);

      free ((char *) directories);

      return (result);
    }

only_filename:

  if (*filename == '\0')
    {
      result = (char **) realloc ((char *) result, 2 * sizeof (char *));
      if (result == NULL)
	{
	  if (free_dirname)
	    free (directory_name);
	  return (NULL);
	}


      if (directory_len > 0 && hasglob == 2 && (flags & GX_RECURSE) != 0)
	{
	  dequote_pathname (directory_name);
	  directory_len = strlen (directory_name);
	}


      if (directory_len > 0 && hasglob == 2 && (flags & GX_RECURSE) == 0)
	{
#if 1
	  dequote_pathname (directory_name);
	  if (glob_testdir (directory_name, 0) < 0)
	    {
	      if (free_dirname)
		free (directory_name);
	      return ((char **)&glob_error_return);
	    }
#else
	  return ((char **)&glob_error_return);
#endif
	}


      result[0] = (char *) malloc (directory_len + 1);
      if (result[0] == NULL)
	goto memory_error;
      bcopy (directory_name, result[0], directory_len + 1);
      if (free_dirname)
	free (directory_name);
      result[1] = NULL;
      return (result);
    }
  else
    {
      char **temp_results;


      if (directory_len > 0)
	dequote_pathname (directory_name);


      free (result);


      dflags = flags & ~GX_MARKDIRS;
      if (directory_len == 0)
	dflags |= GX_NULLDIR;
      if ((flags & GX_GLOBSTAR) && filename[0] == '*' && filename[1] == '*' && filename[2] == '\0')
	{
	  dflags |= GX_ALLDIRS|GX_ADDCURDIR;
#if 0


#endif
	  if (directory_len == 0 && (flags & GX_ALLDIRS) == 0)
	    dflags &= ~GX_ADDCURDIR;
	}
      temp_results = glob_vector (filename,
				  (directory_len == 0 ? "." : directory_name),
				  dflags);

      if (temp_results == NULL || temp_results == (char **)&glob_error_return)
	{
	  if (free_dirname)
	    free (directory_name);
	  QUIT;
	  run_pending_traps ();
	  return (temp_results);
	}

      result = glob_dir_to_array ((dflags & GX_ALLDIRS) ? "" : directory_name, temp_results, flags);

      if (free_dirname)
	free (directory_name);
      return (result);
    }


 memory_error:
  if (result != NULL)
    {
      register unsigned int i;
      for (i = 0; result[i] != NULL; ++i)
	free (result[i]);
      free ((char *) result);
    }

  if (free_dirname && directory_name)
    free (directory_name);

  QUIT;
  run_pending_traps ();

  return (NULL);
}
