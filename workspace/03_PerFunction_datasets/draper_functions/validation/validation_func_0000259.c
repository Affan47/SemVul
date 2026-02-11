_gcry_dsa_gen_k (gcry_mpi_t q, int security_level)
{
  gcry_mpi_t k        = mpi_alloc_secure (mpi_get_nlimbs (q));
  unsigned int nbits  = mpi_get_nbits (q);
  unsigned int nbytes = (nbits+7)/8;
  char *rndbuf = NULL;


  if (DBG_CIPHER)
    log_debug ("choosing a random k of %u bits at seclevel %d\n",
               nbits, security_level);
  for (;;)
    {
      if ( !rndbuf || nbits < 32 )
        {
          xfree (rndbuf);
          rndbuf = _gcry_random_bytes_secure (nbytes, security_level);
	}
      else
        {


          char *pp = _gcry_random_bytes_secure (4, security_level);
          memcpy (rndbuf, pp, 4);
          xfree (pp);
	}
      _gcry_mpi_set_buffer (k, rndbuf, nbytes, 0);


      if (mpi_test_bit (k, nbits-1))
        mpi_set_highbit (k, nbits-1);
      else
        {
          mpi_set_highbit (k, nbits-1);
          mpi_clear_bit (k, nbits-1);
	}

      if (!(mpi_cmp (k, q) < 0))
        {
          if (DBG_CIPHER)
            log_debug ("\tk too large - again\n");
          continue;
        }
      if (!(mpi_cmp_ui (k, 0) > 0))
        {
          if (DBG_CIPHER)
            log_debug ("\tk is zero - again\n");
          continue;
        }
      break;
    }
  xfree (rndbuf);

  return k;
}
