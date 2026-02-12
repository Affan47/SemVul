canonicalize_path (const char *path, char **pcanonical)
{
  char *canonical = 0;

  assert (path && *path);
  assert (pcanonical);

  canonical = MALLOC (char, 1+ LT_STRLEN (path));
  if (!canonical)
    return 1;

  {
    size_t dest = 0;
    size_t src;
    for (src = 0; path[src] != LT_EOS_CHAR; ++src)
      {


	if (path[src] == LT_PATHSEP_CHAR)
	  {
	    if ((dest == 0)
		|| (path[1+ src] == LT_PATHSEP_CHAR)
		|| (path[1+ src] == LT_EOS_CHAR))
	      continue;
	  }


	if ((path[src] != '/')
#if defined(LT_DIRSEP_CHAR)
	    && (path[src] != LT_DIRSEP_CHAR)
#endif
	    )
	  {
	    canonical[dest++] = path[src];
	  }


	else if ((path[1+ src] != LT_PATHSEP_CHAR)
		 && (path[1+ src] != LT_EOS_CHAR)
#if defined(LT_DIRSEP_CHAR)
		 && (path[1+ src] != LT_DIRSEP_CHAR)
#endif
		 && (path[1+ src] != '/'))
	  {
	    canonical[dest++] = '/';
	  }
      }


    canonical[dest] = LT_EOS_CHAR;
  }


  *pcanonical = canonical;

  return 0;
}
