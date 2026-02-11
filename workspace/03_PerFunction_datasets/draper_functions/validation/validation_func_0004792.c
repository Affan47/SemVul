check (long i, mpfr_rnd_t rnd)
{
  mpfr_t f;
  mpz_t z;
  mpfr_exp_t e;
  int inex;


  mpfr_init2 (f, CHAR_BIT * sizeof(long));
  mpz_init (z);
  mpz_set_ui (z, i);

  do
    e = randexp ();
  while (e > mpfr_get_emax () - CHAR_BIT * sizeof(long));
  inex = mpfr_set_z_2exp (f, z, e, rnd);
  if (inex != 0)
    {
      printf ("Error in mpfr_set_z_2exp for i=%ld, e=%ld,"
              " wrong ternary value\n", i, (long) e);
      printf ("expected 0, got %d\n", inex);
      exit (1);
    }
  mpfr_div_2si (f, f, e, rnd);
  if (mpfr_get_si (f, MPFR_RNDZ) != i)
    {
      printf ("Error in mpfr_set_z_2exp for i=%ld e=", i);
      if (e < LONG_MIN)
        printf ("(<LONG_MIN)");
      else if (e > LONG_MAX)
        printf ("(>LONG_MAX)");
      else
        printf ("%ld", (long) e);
      printf (" rnd_mode=%d\n", rnd);
      printf ("expected %ld\n", i);
      printf ("got      "); mpfr_dump (f);
      exit (1);
    }
  mpfr_clear (f);
  mpz_clear (z);
}
