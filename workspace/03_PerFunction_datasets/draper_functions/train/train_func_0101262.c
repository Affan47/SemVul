scripts_argv (const char *file, char *const argv[], int argc, char **new_argv)
{

  new_argv[0] = (char *) _PATH_BSHELL;
  new_argv[1] = (char *) file;
  while (argc > 1)
    {
      new_argv[argc] = argv[argc - 1];
      --argc;
    }
}
