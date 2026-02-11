output_file_close (char *filename)
{
  bfd_boolean res;

  if (stdoutput == NULL)
    return;


  if (had_errors ())
    res = bfd_cache_close_all ();
  else
    res = bfd_close (stdoutput);


  stdoutput = NULL;

  if (! res)
    as_fatal (_("can't close %s: %s"), filename,
	      bfd_errmsg (bfd_get_error ()));
}
