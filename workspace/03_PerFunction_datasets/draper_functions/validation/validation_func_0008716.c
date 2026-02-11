__mpn_extract_long_double (mp_ptr res_ptr, mp_size_t size,
			   int *expt, int *is_neg,
			   long double value)
{
  union ieee854_long_double u;
  u.d = value;

  *is_neg = u.ieee.negative;
  *expt = (int) u.ieee.exponent - IEEE854_LONG_DOUBLE_BIAS;

#if BITS_PER_MP_LIMB == 32
  res_ptr[0] = u.ieee.mantissa1;
  res_ptr[1] = u.ieee.mantissa0;
  #define N 2
#elif BITS_PER_MP_LIMB == 64


  res_ptr[0] = ((mp_limb_t) u.ieee.mantissa0 << 32) | u.ieee.mantissa1;
  #define N 1
#else
  #error "mp_limb size " BITS_PER_MP_LIMB "not accounted for"
#endif

  if (u.ieee.exponent == 0)
    {


      if (res_ptr[0] == 0 && res_ptr[N - 1] == 0)

	*expt = 0;
      else
	{


	  int cnt;


	  res_ptr[N - 1] &= ~(1L << ((LDBL_MANT_DIG - 1) % BITS_PER_MP_LIMB));

	  if (res_ptr[N - 1] != 0)
	    {
	      count_leading_zeros (cnt, res_ptr[N - 1]);
	      if (cnt != 0)
		{
#if N == 2
		  res_ptr[N - 1] = res_ptr[N - 1] << cnt
				   | (res_ptr[0] >> (BITS_PER_MP_LIMB - cnt));
		  res_ptr[0] <<= cnt;
#else
		  res_ptr[N - 1] <<= cnt;
#endif
		}
	      *expt = LDBL_MIN_EXP - 1 - cnt;
	    }
	  else if (res_ptr[0] != 0)
	    {
	      count_leading_zeros (cnt, res_ptr[0]);
	      res_ptr[N - 1] = res_ptr[0] << cnt;
	      res_ptr[0] = 0;
	      *expt = LDBL_MIN_EXP - 1 - BITS_PER_MP_LIMB - cnt;
	    }
	  else
	    {


#if N == 2
	      res_ptr[N - 1] = 0x80000000ul;
#else
	      res_ptr[0] = 0x8000000000000000ul;
#endif
	      *expt = LDBL_MIN_EXP - 1;
	    }
	}
    }
  else if (u.ieee.exponent < 0x7fff
#if N == 2
	   && res_ptr[0] == 0
#endif
	   && res_ptr[N - 1] == 0)

    *expt = 0;

  return N;
}
