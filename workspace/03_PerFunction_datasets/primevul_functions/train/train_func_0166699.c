lt_dlexit (void)
{

  lt_dlloader *loader   = 0;
  lt_dlhandle  handle   = handles;
  int	       errors   = 0;

  if (!initialized)
    {
      LT__SETERROR (SHUTDOWN);
      ++errors;
      goto done;
    }


  if (--initialized == 0)
    {
      int	level;

      while (handles && LT_DLIS_RESIDENT (handles))
	{
	  handles = handles->next;
	}


      for (level = 1; handle; ++level)
	{
	  lt_dlhandle cur = handles;
	  int saw_nonresident = 0;

	  while (cur)
	    {
	      lt_dlhandle tmp = cur;
	      cur = cur->next;
	      if (!LT_DLIS_RESIDENT (tmp))
		{
		  saw_nonresident = 1;
		  if (tmp->info.ref_count <= level)
		    {
		      if (lt_dlclose (tmp))
			{
			  ++errors;
			}


		      if (cur)
			{
			  for (tmp = handles; tmp; tmp = tmp->next)
			    if (tmp == cur)
			      break;
			  if (! tmp)
			    cur = handles;
			}
		    }
		}
	    }

	  if (!saw_nonresident)
	    break;
	}


      if (!errors)
	LT__SETERRORSTR (0);


      for (loader = (lt_dlloader *) lt_dlloader_next (NULL); loader;)
	{
	  lt_dlloader *next   = (lt_dlloader *) lt_dlloader_next (loader);
	  lt_dlvtable *vtable = (lt_dlvtable *) lt_dlloader_get (loader);

	  if ((vtable = lt_dlloader_remove ((char *) vtable->name)))
	    {
	      FREE (vtable);
	    }
	  else
	    {

	      const char *err;
	      LT__GETERROR (err);
	      if (err)
		++errors;
	    }

	  loader = next;
	}

      FREE(user_search_path);
    }

 done:
  return errors;
}
