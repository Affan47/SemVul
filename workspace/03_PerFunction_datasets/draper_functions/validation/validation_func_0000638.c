refmpn_mod2 (mp_limb_t r[2], const mp_limb_t a[2], const mp_limb_t d[2])
{
  mp_limb_t  D[2];
  int        n;

  ASSERT (! refmpn_overlap_p (r, (mp_size_t) 2, d, (mp_size_t) 2));
  ASSERT_MPN (a, 2);
  ASSERT_MPN (d, 2);

  D[1] = d[1], D[0] = d[0];
  r[1] = a[1], r[0] = a[0];
  n = 0;

  for (;;)
    {
      if (D[1] & GMP_NUMB_HIGHBIT)
	break;
      if (refmpn_cmp (r, D, (mp_size_t) 2) <= 0)
	break;
      refmpn_lshift (D, D, (mp_size_t) 2, 1);
      n++;
      ASSERT (n <= GMP_NUMB_BITS);
    }

  while (n >= 0)
    {
      if (refmpn_cmp (r, D, (mp_size_t) 2) >= 0)
	ASSERT_NOCARRY (refmpn_sub_n (r, r, D, (mp_size_t) 2));
      refmpn_rshift (D, D, (mp_size_t) 2, 1);
      n--;
    }

  ASSERT (refmpn_cmp (r, d, (mp_size_t) 2) < 0);
}
