wgetrc_user_file_name (void)
{
  char *home;
  char *file = NULL;


#ifdef __VMS
  file = "SYS$LOGIN:.wgetrc";
#else
  home = home_dir ();
  if (home)
    file = aprintf ("%s/.wgetrc", home);
  xfree_null (home);
#endif

  if (!file)
    return NULL;
  if (!file_exists_p (file))
    {
      xfree (file);
      return NULL;
    }
  return file;
}
