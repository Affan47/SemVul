lt_dlclose (lt_dlhandle handle)
{
  lt_dlhandle cur, last;
  int errors = 0;


  last = cur = handles;
  while (cur && handle != cur)
    {
      last = cur;
      cur = cur->next;
    }

  if (!cur)
    {
      LT__SETERROR (INVALID_HANDLE);
      ++errors;
      goto done;
    }

  cur = handle;
  cur->info.ref_count--;


  if (cur->info.ref_count <= 0 && !LT_DLIS_RESIDENT (cur))
    {
      lt_user_data data = cur->vtable->dlloader_data;

      if (cur != handles)
	{
	  last->next = cur->next;
	}
      else
	{
	  handles = cur->next;
	}

      errors += cur->vtable->module_close (data, cur->module);
      errors += unload_deplibs (handle);


      FREE (cur->interface_data);

      FREE (cur->info.filename);
      FREE (cur->info.name);
      FREE (cur);

      goto done;
    }

  if (LT_DLIS_RESIDENT (handle))
    {
      LT__SETERROR (CLOSE_RESIDENT_MODULE);
      ++errors;
    }

 done:
  return errors;
}
