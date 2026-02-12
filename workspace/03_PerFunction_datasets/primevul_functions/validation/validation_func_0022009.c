cpio_create_dir (struct cpio_file_stat *file_hdr, int existing_dir)
{
  int res;
  int setstat_delayed = 0;

  if (to_stdout_option)
    return 0;


  strip_trailing_slashes (file_hdr->c_name);


  if (file_hdr->c_name[0] == '.' && file_hdr->c_name[1] == '\0')
    {
      return 0;
    }

  if (!existing_dir)
    res = cpio_mkdir (file_hdr, &setstat_delayed);
  else
    res = 0;
  if (res < 0 && create_dir_flag)
    {
      create_all_directories (file_hdr->c_name);
      res = cpio_mkdir (file_hdr, &setstat_delayed);
    }
  if (res < 0)
    {


      struct stat file_stat;
      if (errno != EEXIST)
	{
	  mkdir_error (file_hdr->c_name);
	  return -1;
	}
      if (lstat (file_hdr->c_name, &file_stat))
	{
	  stat_error (file_hdr->c_name);
	  return -1;
	}
      if (!(S_ISDIR (file_stat.st_mode)))
	{
	  error (0, 0, _("%s is not a directory"),
		 quotearg_colon (file_hdr->c_name));
	  return -1;
	}
    }

  if (!setstat_delayed && repair_delayed_set_stat (file_hdr))
    set_perms (-1, file_hdr);
  return 0;
}
