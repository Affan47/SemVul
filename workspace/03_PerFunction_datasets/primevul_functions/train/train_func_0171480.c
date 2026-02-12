int handler::delete_table(const char *name)
{
  int saved_error= 0;
  int error= 0;
  int enoent_or_zero;

  if (ht->discover_table)
    enoent_or_zero= 0;
  else
    enoent_or_zero= ENOENT;

  for (const char **ext=bas_ext(); *ext ; ext++)
  {
    if (mysql_file_delete_with_symlink(key_file_misc, name, *ext, 0))
    {
      if (my_errno != ENOENT)
      {


        if (enoent_or_zero)
          return my_errno;
	saved_error= my_errno;
      }
    }
    else
      enoent_or_zero= 0;
    error= enoent_or_zero;
  }
  return saved_error ? saved_error : error;
}
