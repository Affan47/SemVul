mpz_absadd_2exp (mpz_t RS, unsigned int e)
{
  mp_size_t siz, limb_idx, bit_idx;
  mp_limb_t cy;
  int sgn;

  limb_idx = e / GMP_NUMB_BITS;
  bit_idx = e % GMP_NUMB_BITS;
  siz = mpz_size (RS);
  sgn = (mpz_sgn (RS) >= 0) ? 1 : -1;

  if (limb_idx >= RS->_mp_alloc)

    mpz_realloc2 (RS, (limb_idx + 1) * GMP_NUMB_BITS);


  while (siz <= limb_idx)
    {
      RS->_mp_d[siz++] = 0;
      RS->_mp_size += sgn;
    }


  cy = mpn_add_1 (RS->_mp_d + limb_idx, RS->_mp_d + limb_idx,
                  siz - limb_idx, ((mp_limb_t)1) << bit_idx);
  if (cy)
    {
      if (RS->_mp_alloc <= siz)

        mpz_realloc2 (RS, (siz + 1) * GMP_NUMB_BITS);

      RS->_mp_d[siz] = 1;
      RS->_mp_size += sgn;
    }
}
