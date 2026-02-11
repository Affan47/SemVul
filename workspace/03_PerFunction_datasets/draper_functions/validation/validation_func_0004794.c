s_mp_mul_d(mp_int *a, mp_digit d)
{
  mp_err  res;
  mp_size used;
  int     pow;

  if (!d) {
    mp_zero(a);
    return MP_OKAY;
  }
  if (d == 1)
    return MP_OKAY;
  if (0 <= (pow = s_mp_ispow2d(d))) {
    return s_mp_mul_2d(a, (mp_digit)pow);
  }

  used = MP_USED(a);
  MP_CHECKOK( s_mp_pad(a, used + 1) );

  s_mpv_mul_d(MP_DIGITS(a), used, d, MP_DIGITS(a));

  s_mp_clamp(a);

CLEANUP:
  return res;

}
