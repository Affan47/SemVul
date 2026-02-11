s_mpv_sqr_add_prop(const mp_digit *pa, mp_size a_len, mp_digit *ps)
{
#if !defined(MP_NO_MP_WORD) && !defined(MP_NO_MUL_WORD)
  mp_word  w;
  mp_digit d;
  mp_size  ix;

  w  = 0;
#define ADD_SQUARE(n) \
    d = pa[n]; \
    w += (d * (mp_word)d) + ps[2*n]; \
    ps[2*n] = ACCUM(w); \
    w = (w >> DIGIT_BIT) + ps[2*n+1]; \
    ps[2*n+1] = ACCUM(w); \
    w = (w >> DIGIT_BIT)

  for (ix = a_len; ix >= 4; ix -= 4) {
    ADD_SQUARE(0);
    ADD_SQUARE(1);
    ADD_SQUARE(2);
    ADD_SQUARE(3);
    pa += 4;
    ps += 8;
  }
  if (ix) {
    ps += 2*ix;
    pa += ix;
    switch (ix) {
    case 3: ADD_SQUARE(-3);
    case 2: ADD_SQUARE(-2);
    case 1: ADD_SQUARE(-1);
    case 0: break;
    }
  }
  while (w) {
    w += *ps;
    *ps++ = ACCUM(w);
    w = (w >> DIGIT_BIT);
  }
#else
  mp_digit carry = 0;
  while (a_len--) {
    mp_digit a_i = *pa++;
    mp_digit a0a0, a1a1;

    MP_SQR_D(a_i, a1a1, a0a0);


    a0a0 += carry;
    if (a0a0 < carry)
      ++a1a1;


    a0a0 += a_i = *ps;
    if (a0a0 < a_i)
      ++a1a1;
    *ps++ = a0a0;
    a1a1 += a_i = *ps;
    carry = (a1a1 < a_i);
    *ps++ = a1a1;
  }
  while (carry) {
    mp_digit s_i = *ps;
    carry += s_i;
    *ps++ = carry;
    carry = carry < s_i;
  }
#endif
}
