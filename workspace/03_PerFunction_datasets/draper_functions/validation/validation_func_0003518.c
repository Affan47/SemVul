remove_parents (char *dir)
{
  char *slash;
  bool ok = true;

  strip_trailing_slashes (dir);
  while (1)
    {
      slash = strrchr (dir, '/');
      if (slash == NULL)
        break;


      while (slash > dir && *slash == '/')
        --slash;
      slash[1] = 0;


      if (verbose)
        prog_fprintf (stdout, _("removing directory, %s"), quote (dir));

      ok = (rmdir (dir) == 0);

      if (!ok)
        {

          if (ignorable_failure (errno, dir))
            {
              ok = true;
            }
          else
            {

              error (0, errno, _("failed to remove directory %s"),
                     quote (dir));
            }
          break;
        }
    }
  return ok;
}
