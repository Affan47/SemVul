mpz_normalize (mpz_t rop, mpz_t z, mpfr_exp_t q)
{
  size_t k;

  MPFR_MPZ_SIZEINBASE2 (k, z);
  MPFR_ASSERTD (k == (mpfr_uexp_t) k);
  if (q < 0 || (mpfr_uexp_t) k > (mpfr_uexp_t) q)
    {
      mpz_fdiv_q_2exp (rop, z, (unsigned long) ((mpfr_uexp_t) k - q));
      return (mpfr_exp_t) k - q;
    }
  if (MPFR_UNLIKELY(rop != z))
    mpz_set (rop, z);
  return 0;
}
