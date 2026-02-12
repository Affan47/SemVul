lt_dlinit (void)
{
  int	errors	= 0;


  if (++initialized == 1)
    {
      lt__alloc_die	= lt__alloc_die_callback;
      handles		= 0;
      user_search_path	= 0;


      errors += loader_init (get_vtable, 0);


#ifdef HAVE_LIBDLLOADER
      if (!errors)
	{
	  errors += lt_dlpreload (&preloaded_symbols);
	}

      if (!errors)
	{
	  errors += lt_dlpreload_open (LT_STR(LTDLOPEN), loader_init_callback);
	}
#endif
    }

#ifdef LT_DEBUG_LOADERS
  lt_dlloader_dump();
#endif

  return errors;
}
