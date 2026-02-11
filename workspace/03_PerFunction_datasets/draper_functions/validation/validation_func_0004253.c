bfd_cache_delete (bfd *abfd)
{
  bfd_boolean ret;

  if (fclose ((FILE *) abfd->iostream) == 0)
    ret = TRUE;
  else
    {
      ret = FALSE;
      bfd_set_error (bfd_error_system_call);
    }

  snip (abfd);

  abfd->iostream = NULL;
  --open_files;

  return ret;
}
