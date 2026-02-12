int my_progress_callback(void *d, enum LibRaw_progress p, int iteration,
                         int expected)
{
  char *passed = (char *)(d ? d : "default string");


  if (verbosity > 2)
  {
    printf("CB: %s  pass %d of %d (data passed=%s)\n", libraw_strprogress(p),
           iteration, expected, passed);
  }
  else if (iteration == 0)
    printf("Starting %s (expecting %d iterations)\n", libraw_strprogress(p),
           expected);
  else if (iteration == expected - 1)
    printf("%s finished\n", libraw_strprogress(p));


  return 0;
}
