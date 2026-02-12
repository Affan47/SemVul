generate ( ELG_secret_key *sk, unsigned int nbits, gcry_mpi_t **ret_factors )
{
  gcry_err_code_t rc;
  gcry_mpi_t p;
  gcry_mpi_t p_min1;
  gcry_mpi_t g;
  gcry_mpi_t x;
  gcry_mpi_t y;
  unsigned int qbits;
  unsigned int xbits;
  byte *rndbuf;

  p_min1 = mpi_new ( nbits );
  qbits = wiener_map( nbits );
  if( qbits & 1 )
    qbits++;
  g = mpi_alloc(1);
  rc = _gcry_generate_elg_prime (0, nbits, qbits, g, &p, ret_factors);
  if (rc)
    {
      mpi_free (p_min1);
      mpi_free (g);
      return rc;
    }
  mpi_sub_ui(p_min1, p, 1);


  xbits = qbits * 3 / 2;
  if( xbits >= nbits )
    BUG();
  x = mpi_snew ( xbits );
  if( DBG_CIPHER )
    log_debug("choosing a random x of size %u\n", xbits );
  rndbuf = NULL;
  do
    {
      if( DBG_CIPHER )
        progress('.');
      if( rndbuf )
        {
          if( xbits < 16 )
            {
              xfree(rndbuf);
              rndbuf = _gcry_random_bytes_secure ((xbits+7)/8,
                                                  GCRY_VERY_STRONG_RANDOM);
            }
          else
            {
              char *r = _gcry_random_bytes_secure (2, GCRY_VERY_STRONG_RANDOM);
              memcpy(rndbuf, r, 2 );
              xfree (r);
            }
	}
      else
        {
          rndbuf = _gcry_random_bytes_secure ((xbits+7)/8,
                                              GCRY_VERY_STRONG_RANDOM );
	}
      _gcry_mpi_set_buffer( x, rndbuf, (xbits+7)/8, 0 );
      mpi_clear_highbit( x, xbits+1 );
    }
  while( !( mpi_cmp_ui( x, 0 )>0 && mpi_cmp( x, p_min1 )<0 ) );
  xfree(rndbuf);

  y = mpi_new (nbits);
  mpi_powm( y, g, x, p );

  if( DBG_CIPHER )
    {
      progress ('\n');
      log_mpidump ("elg  p", p );
      log_mpidump ("elg  g", g );
      log_mpidump ("elg  y", y );
      log_mpidump ("elg  x", x );
    }


  sk->p = p;
  sk->g = g;
  sk->y = y;
  sk->x = x;

  _gcry_mpi_release ( p_min1 );


  test_keys ( sk, nbits - 64, 0 );

  return 0;
}
