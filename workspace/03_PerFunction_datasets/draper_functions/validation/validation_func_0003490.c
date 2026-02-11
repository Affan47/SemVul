bignum_remainder_unsigned_small_denominator(
       bignum_type n, bignum_digit_type d, int negative_p)
{
  bignum_digit_type two_digits;
  bignum_digit_type * start = (BIGNUM_START_PTR (n));
  bignum_digit_type * scan = (start + (BIGNUM_LENGTH (n)));
  bignum_digit_type r = 0;
  BIGNUM_ASSERT ((d > 1) && (d < BIGNUM_RADIX_ROOT));
  while (start < scan)
    {
      two_digits = (*--scan);
      r =
        ((HD_CONS (((HD_CONS (r, (HD_HIGH (two_digits)))) % d),
                   (HD_LOW (two_digits))))
         % d);
    }
  return (bignum_digit_to_bignum (r, negative_p));
}
