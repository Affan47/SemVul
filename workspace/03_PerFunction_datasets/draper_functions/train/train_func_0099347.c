filename_to_uri (const char *path)
{
  struct stat st;
  char *mrl;

  if (stat (path, &st))
    st.st_mode = 0;

  if ((mrl = filename_to_dvd (path, &st)))
    return mrl;

  if ((mrl = filename_to_vcd (path, &st)))
    return mrl;

  return g_filename_to_uri (path, NULL, NULL);
}
