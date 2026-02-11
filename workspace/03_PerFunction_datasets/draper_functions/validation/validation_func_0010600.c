test_create (void)
{
  double *test;
  int     i;

  srandom (20050728);

  test = babl_malloc (sizeof (double) * test_pixels * 4);

  for (i = 0; i < test_pixels * 4; i++)
    test [i] = ((double) random () / RAND_MAX) * 1.4 - 0.2;

  return test;
}
