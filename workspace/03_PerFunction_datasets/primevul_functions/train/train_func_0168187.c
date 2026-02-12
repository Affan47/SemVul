set_file_timestamp (struct http_stat *hs)
{
  size_t filename_len = strlen (hs->local_file);
  char *filename_plus_orig_suffix = alloca (filename_len + sizeof (ORIG_SFX));
  bool local_dot_orig_file_exists = false;
  char *local_filename = NULL;
  struct stat st;

  if (opt.backup_converted)


    {


      memcpy (filename_plus_orig_suffix, hs->local_file, filename_len);
      memcpy (filename_plus_orig_suffix + filename_len,
              ORIG_SFX, sizeof (ORIG_SFX));


      if (stat (filename_plus_orig_suffix, &st) == 0)
        {
          local_dot_orig_file_exists = true;
          local_filename = filename_plus_orig_suffix;
        }
    }

  if (!local_dot_orig_file_exists)

    if (stat (hs->local_file, &st) == 0)
      local_filename = hs->local_file;

  if (local_filename != NULL)


    {
      hs->orig_file_name = xstrdup (local_filename);
      hs->orig_file_size = st.st_size;
      hs->orig_file_tstamp = st.st_mtime;
#ifdef WINDOWS


      ++hs->orig_file_tstamp;
#endif
      hs->timestamp_checked = true;
    }

  return RETROK;
}
