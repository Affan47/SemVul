one_test (mpz_t a, mpz_t b, int i)
{
  struct hgcd_matrix hgcd;
  struct hgcd_ref ref;

  mpz_t ref_r0;
  mpz_t ref_r1;
  mpz_t hgcd_r0;
  mpz_t hgcd_r1;

  mp_size_t res[2];
  mp_size_t asize;
  mp_size_t bsize;

  mp_size_t hgcd_init_scratch;
  mp_size_t hgcd_scratch;

  mp_ptr hgcd_init_tp;
  mp_ptr hgcd_tp;

  asize = a->_mp_size;
  bsize = b->_mp_size;

  ASSERT (asize >= bsize);

  hgcd_init_scratch = MPN_HGCD_MATRIX_INIT_ITCH (asize);
  hgcd_init_tp = refmpn_malloc_limbs (hgcd_init_scratch);
  mpn_hgcd_matrix_init (&hgcd, asize, hgcd_init_tp);

  hgcd_scratch = mpn_hgcd_itch (asize);
  hgcd_tp = refmpn_malloc_limbs (hgcd_scratch);

#if 0
  fprintf (stderr,
	   "one_test: i = %d asize = %d, bsize = %d\n",
	   i, a->_mp_size, b->_mp_size);

  gmp_fprintf (stderr,
	       "one_test: i = %d\n"
	       "  a = %Zx\n"
	       "  b = %Zx\n",
	       i, a, b);
#endif
  hgcd_ref_init (&ref);

  mpz_init_set (ref_r0, a);
  mpz_init_set (ref_r1, b);
  res[0] = hgcd_ref (&ref, ref_r0, ref_r1);

  mpz_init_set (hgcd_r0, a);
  mpz_init_set (hgcd_r1, b);
  if (bsize < asize)
    {
      _mpz_realloc (hgcd_r1, asize);
      MPN_ZERO (hgcd_r1->_mp_d + bsize, asize - bsize);
    }
  res[1] = mpn_hgcd (hgcd_r0->_mp_d,
		     hgcd_r1->_mp_d,
		     asize,
		     &hgcd, hgcd_tp);

  if (res[0] != res[1])
    {
      fprintf (stderr, "ERROR in test %d\n", i);
      fprintf (stderr, "Different return value from hgcd and hgcd_ref\n");
      fprintf (stderr, "op1=");                 debug_mp (a, -16);
      fprintf (stderr, "op2=");                 debug_mp (b, -16);
      fprintf (stderr, "hgcd_ref: %ld\n", (long) res[0]);
      fprintf (stderr, "mpn_hgcd: %ld\n", (long) res[1]);
      abort ();
    }
  if (res[0] > 0)
    {
      if (!hgcd_ref_equal (&hgcd, &ref)
	  || !mpz_mpn_equal (ref_r0, hgcd_r0->_mp_d, res[1])
	  || !mpz_mpn_equal (ref_r1, hgcd_r1->_mp_d, res[1]))
	{
	  fprintf (stderr, "ERROR in test %d\n", i);
	  fprintf (stderr, "mpn_hgcd and hgcd_ref returned different values\n");
	  fprintf (stderr, "op1=");                 debug_mp (a, -16);
	  fprintf (stderr, "op2=");                 debug_mp (b, -16);
	  abort ();
	}
    }

  refmpn_free_limbs (hgcd_init_tp);
  refmpn_free_limbs (hgcd_tp);
  hgcd_ref_clear (&ref);
  mpz_clear (ref_r0);
  mpz_clear (ref_r1);
  mpz_clear (hgcd_r0);
  mpz_clear (hgcd_r1);

  return res[0];
}
