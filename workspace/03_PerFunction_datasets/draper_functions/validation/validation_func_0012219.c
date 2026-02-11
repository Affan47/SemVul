check_uj (uintmax_t u, mpfr_ptr x)
{
  mpfr_t y;
  int i;

  mpfr_init2 (y, MPFR_PREC (x));

  for (i = -1; i <= 1; i++)
    {
      int rnd;

      mpfr_set_si_2exp (y, i, -2, MPFR_RNDN);
      mpfr_add (y, y, x, MPFR_RNDN);
      for (rnd = 0; rnd < MPFR_RND_MAX; rnd++)
        {
          uintmax_t r;

          if (rnd == MPFR_RNDZ && i < 0)
            continue;
          if (rnd == MPFR_RNDD && i < 0)
            continue;
          if (rnd == MPFR_RNDU && i > 0)
            continue;
          if (rnd == MPFR_RNDA && ((MPFR_IS_POS(y) && i > 0) ||
                                  (MPFR_IS_NEG(y) && i < 0)))
            continue;

          r = mpfr_get_uj (y, (mpfr_rnd_t) rnd);
          if (r != u)
            {
              printf ("Error in check_uj for y = ");
              mpfr_out_str (stdout, 2, 0, y, MPFR_RNDN);
              printf (" in %s\n", mpfr_print_rnd_mode ((mpfr_rnd_t) rnd));
              printf ("Got %ju instead of %ju.\n", r, u);
              exit (1);
            }
        }
    }

  mpfr_clear (y);
}
