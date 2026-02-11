mp_mod (mp_int * a, mp_int * b, mp_int * c)
{
  mp_int  t;
  int     res;

  if ((res = mp_init (&t)) != MP_OKAY) {
    return res;
  }

  if ((res = mp_div (a, b, NULL, &t)) != MP_OKAY) {
    mp_clear (&t);
    return res;
  }

  if (mp_iszero(&t) || t.sign == b->sign) {
    res = MP_OKAY;
    mp_exch (&t, c);
  } else {
    res = mp_add (b, &t, c);
  }

  mp_clear (&t);
  return res;
}
