mp_add(const mp_int *a, const mp_int *b, mp_int *c)
{
  mp_err  res;

  ARGCHK(a != NULL && b != NULL && c != NULL, MP_BADARG);

  if(SIGN(a) == SIGN(b)) {
    MP_CHECKOK( s_mp_add_3arg(a, b, c) );
  } else if(s_mp_cmp(a, b) >= 0) {
    MP_CHECKOK( s_mp_sub_3arg(a, b, c) );
  } else {
    MP_CHECKOK( s_mp_sub_3arg(b, a, c) );
  }

  if (s_mp_cmp_d(c, 0) == MP_EQ)
    SIGN(c) = ZPOS;

CLEANUP:
  return res;

}
