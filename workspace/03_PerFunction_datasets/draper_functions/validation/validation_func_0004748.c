dupargv (char **argv)
{
  int argc;
  char **copy;

  if (argv == NULL)
    return NULL;


  for (argc = 0; argv[argc] != NULL; argc++);
  copy = (char **) malloc ((argc + 1) * sizeof (char *));
  if (copy == NULL)
    return NULL;


  for (argc = 0; argv[argc] != NULL; argc++)
    {
      int len = strlen (argv[argc]);
      copy[argc] = (char *) malloc (len + 1);
      if (copy[argc] == NULL)
	{
	  freeargv (copy);
	  return NULL;
	}
      strcpy (copy[argc], argv[argc]);
    }
  copy[argc] = NULL;
  return copy;
}
