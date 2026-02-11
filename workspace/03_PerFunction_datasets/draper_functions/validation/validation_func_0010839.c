delete_if_ordinary (const char *name)
{
  struct stat st;
#ifdef DEBUG
  int i, c;

  printf ("Delete %s? (y or n) ", name);
  fflush (stdout);
  i = getchar ();
  if (i != '\n')
    while ((c = getchar ()) != '\n' && c != EOF)
      ;

  if (i == 'y' || i == 'Y')
#endif
  DELETE_IF_ORDINARY (name, st, verbose_flag);
}
