is_prime (gcry_mpi_t n, int steps, GNUNET_HashCode * hc)
{
  gcry_mpi_t x;
  gcry_mpi_t y;
  gcry_mpi_t z;
  gcry_mpi_t nminus1;
  gcry_mpi_t a2;
  gcry_mpi_t q;
  unsigned int i, j, k;
  int rc = 0;
  unsigned int nbits;

  x = gcry_mpi_new (0);
  y = gcry_mpi_new (0);
  z = gcry_mpi_new (0);
  nminus1 = gcry_mpi_new (0);
  a2 = gcry_mpi_set_ui (NULL, 2);

  nbits = gcry_mpi_get_nbits (n);
  gcry_mpi_sub_ui (nminus1, n, 1);


  q = gcry_mpi_set (NULL, nminus1);
  k = mpz_trailing_zeroes (q);
  mpz_tdiv_q_2exp (q, q, k);

  for (i = 0; i < steps; i++)
  {
    if (!i)
    {
      gcry_mpi_set_ui (x, 2);
    }
    else
    {
      mpz_randomize (x, nbits - 1, hc);
      GNUNET_assert (gcry_mpi_cmp (x, nminus1) < 0);
      GNUNET_assert (gcry_mpi_cmp_ui (x, 1) > 0);
    }
    gcry_mpi_powm (y, x, q, n);
    if (gcry_mpi_cmp_ui (y, 1) && gcry_mpi_cmp (y, nminus1))
    {
      for (j = 1; j < k && gcry_mpi_cmp (y, nminus1); j++)
      {
        gcry_mpi_powm (y, y, a2, n);
        if (!gcry_mpi_cmp_ui (y, 1))
          goto leave;
      }
      if (gcry_mpi_cmp (y, nminus1))
        goto leave;
    }
  }
  rc = 1;

leave:
  gcry_mpi_release (x);
  gcry_mpi_release (y);
  gcry_mpi_release (z);
  gcry_mpi_release (nminus1);
  gcry_mpi_release (q);
  gcry_mpi_release (a2);

  return rc;
}
