mp_read_radix(mp_int *mp, const char *str, int radix)
{
  int     ix = 0, val = 0;
  mp_err  res;
  mp_sign sig = ZPOS;

  ARGCHK(mp != NULL && str != NULL && radix >= 2 && radix <= MAX_RADIX,
	 MP_BADARG);

  mp_zero(mp);


  while(str[ix] &&
	(s_mp_tovalue(str[ix], radix) < 0) &&
	str[ix] != '-' &&
	str[ix] != '+') {
    ++ix;
  }

  if(str[ix] == '-') {
    sig = NEG;
    ++ix;
  } else if(str[ix] == '+') {
    sig = ZPOS;
    ++ix;
  }

  while((val = s_mp_tovalue(str[ix], radix)) >= 0) {
    if((res = s_mp_mul_d(mp, radix)) != MP_OKAY)
      return res;
    if((res = s_mp_add_d(mp, val)) != MP_OKAY)
      return res;
    ++ix;
  }

  if(s_mp_cmp_d(mp, 0) == MP_EQ)
    SIGN(mp) = ZPOS;
  else
    SIGN(mp) = sig;

  return MP_OKAY;

}
