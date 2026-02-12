lt_dlopenadvise (const char *filename, lt_dladvise advise)
{
  lt_dlhandle	handle	= 0;
  int		errors	= 0;
  const char *	saved_error	= 0;

  LT__GETERROR (saved_error);


  if (advise && advise->is_symlocal && advise->is_symglobal)
    {
      LT__SETERROR (CONFLICTING_FLAGS);
      return 0;
    }

  if (!filename
      || !advise
      || !advise->try_ext
      || has_library_ext (filename))
    {


      if (try_dlopen (&handle, filename, NULL, advise) != 0)
	return 0;

      return handle;
    }
  else if (filename && *filename)
    {


      errors += try_dlopen (&handle, filename, archive_ext, advise);


      if (handle || ((errors > 0) && !file_not_found ()))
	return handle;

#if defined(LT_MODULE_EXT)

      LT__SETERRORSTR (saved_error);
      errors = try_dlopen (&handle, filename, shlib_ext, advise);


      if (handle || ((errors > 0) && !file_not_found ()))
	return handle;
#endif
    }


  LT__SETERROR (FILE_NOT_FOUND);
  return 0;
}
