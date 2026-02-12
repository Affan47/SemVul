gen_k( gcry_mpi_t p, int small_k )
{
  gcry_mpi_t k = mpi_alloc_secure( 0 );
  gcry_mpi_t temp = mpi_alloc( mpi_get_nlimbs(p) );
  gcry_mpi_t p_1 = mpi_copy(p);
  unsigned int orig_nbits = mpi_get_nbits(p);
  unsigned int nbits, nbytes;
  char *rndbuf = NULL;

  if (small_k)
    {


      nbits = wiener_map( orig_nbits ) * 3 / 2;
      if( nbits >= orig_nbits )
        BUG();
    }
  else
    nbits = orig_nbits;


  nbytes = (nbits+7)/8;
  if( DBG_CIPHER )
    log_debug("choosing a random k ");
  mpi_sub_ui( p_1, p, 1);
  for(;;)
    {
      if( !rndbuf || nbits < 32 )
        {
          gcry_free(rndbuf);
          rndbuf = gcry_random_bytes_secure( nbytes, GCRY_STRONG_RANDOM );
        }
      else
        {


          char *pp = gcry_random_bytes_secure( 4, GCRY_STRONG_RANDOM );
          memcpy( rndbuf, pp, 4 );
          gcry_free(pp);
	}
      _gcry_mpi_set_buffer( k, rndbuf, nbytes, 0 );

      for(;;)
        {
          if( !(mpi_cmp( k, p_1 ) < 0) )
            {
              if( DBG_CIPHER )
                progress('+');
              break;
            }
          if( !(mpi_cmp_ui( k, 0 ) > 0) )
            {
              if( DBG_CIPHER )
                progress('-');
              break;
            }
          if (gcry_mpi_gcd( temp, k, p_1 ))
            goto found;
          mpi_add_ui( k, k, 1 );
          if( DBG_CIPHER )
            progress('.');
	}
    }
 found:
  gcry_free(rndbuf);
  if( DBG_CIPHER )
    progress('\n');
  mpi_free(p_1);
  mpi_free(temp);

  return k;
}
