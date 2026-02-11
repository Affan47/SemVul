cmpmul (mpc_srcptr x, mpc_srcptr y, mpc_rnd_t rnd)


{
   mpc_t z, t;
   int   inex_z, inex_t;

   mpc_init2 (z, MPC_MAX_PREC (x));
   mpc_init2 (t, MPC_MAX_PREC (x));

   inex_z = mpc_mul_naive (z, x, y, rnd);
   inex_t = mpc_mul_karatsuba (t, x, y, rnd);

   if (mpc_cmp (z, t) != 0 || inex_z != inex_t) {
      fprintf (stderr, "mul_naive and mul_karatsuba differ for rnd=(%s,%s)\n",
               mpfr_print_rnd_mode(MPC_RND_RE(rnd)),
               mpfr_print_rnd_mode(MPC_RND_IM(rnd)));
      MPC_OUT (x);
      MPC_OUT (y);
      MPC_OUT (z);
      MPC_OUT (t);
      if (inex_z != inex_t) {
         fprintf (stderr, "inex_re (z): %s\n", MPC_INEX_STR (inex_z));
         fprintf (stderr, "inex_re (t): %s\n", MPC_INEX_STR (inex_t));
      }
      exit (1);
   }

   mpc_clear (z);
   mpc_clear (t);
}
