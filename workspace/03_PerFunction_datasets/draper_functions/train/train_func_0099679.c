p_load_points(char *filename)
{
  gint l_rc;
  gint l_errno;

  l_rc = gap_mov_exec_gap_load_pointfile(filename, pvals);
  l_errno = errno;

  if (l_rc < -1)
  {
    p_reset_points();
  }
  if (l_rc != 0)
  {
    if(l_errno != 0)
    {
      g_message(_("ERROR: Could not open controlpoints\n"
                "filename: '%s'\n%s")
               ,filename, g_strerror (l_errno));
    }
    else
    {
      g_message(_("ERROR: Could not read controlpoints\n"
                "filename: '%s'\n(Is not a valid controlpoint file)")
               ,filename);
    }
  }
}
