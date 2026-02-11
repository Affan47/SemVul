exp_range (void)
{
  mpfr_t x;
  mpfr_exp_t emin;

  emin = mpfr_get_emin ();
  set_emin (3);
  mpfr_init2 (x, 8);
  mpfr_set_ui (x, 5, MPFR_RNDN);
  mpfr_exp2 (x, x, MPFR_RNDN);
  set_emin (emin);
  if (mpfr_nan_p (x) || mpfr_cmp_ui (x, 32) != 0)
    {
      printf ("Error in mpfr_exp2 for x = 5, with emin = 3\n");
      printf ("Expected 32, got ");
      mpfr_out_str (stdout, 2, 0, x, MPFR_RNDN);
      printf ("\n");
      exit (1);
    }
  mpfr_clear (x);
}
