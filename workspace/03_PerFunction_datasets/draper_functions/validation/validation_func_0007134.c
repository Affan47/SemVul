kb_drand()
{
  unsigned long y;


  if(kr == NR){
    int kk;
    if ( initflag == 0 ) kb_initr(1);
    for (kk=0;kk<N-M;kk++) {
      y = (ptgfsr[kk]&UPPER_MASK)|(ptgfsr[kk+1]&LOWER_MASK);
      ptgfsr[kk] = ptgfsr[kk+M] ^ (y >> 1) ^ mag01[y & 0x1];
    }
    for (;kk<N-1;kk++) {
      y = (ptgfsr[kk]&UPPER_MASK)|(ptgfsr[kk+1]&LOWER_MASK);
      ptgfsr[kk] = ptgfsr[kk+(M-N)] ^ (y >> 1) ^ mag01[y & 0x1];
    }
    y = (ptgfsr[N-1]&UPPER_MASK)|(ptgfsr[0]&LOWER_MASK);
    ptgfsr[N-1] = ptgfsr[M-1] ^ (y >> 1) ^ mag01[y & 0x1];

    for ( k = 0 ; k < N ; k++ )
    { y = ptgfsr[k];
      y ^= TEMPERING_SHIFT_U(y);
      y ^= TEMPERING_SHIFT_S(y) & TEMPERING_MASK_B;
      y ^= TEMPERING_SHIFT_T(y) & TEMPERING_MASK_C;
      y &= 0xffffffff;
      y ^= TEMPERING_SHIFT_L(y);
      ptgfsr[k] = y;
    }

    for ( kr = 0 ; kr < NR ; kr++ )
      drands[kr] = (ptgfsr[2*kr]*rfactor + ptgfsr[2*kr+1])*rfactor;

    k = 0;
    kr = 0;
  }

  return drands[kr++];
}
