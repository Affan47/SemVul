C_i_o_fixnum_quotient(C_word n1, C_word n2)
{
  C_word x1, x2;
#ifdef C_SIXTY_FOUR
  static long eight_0 = 0x8000000000000000L;
#else
  static int eight_0 = 0x80000000;
#endif

  if((n1 & C_FIXNUM_BIT) == 0 || (n2 & C_FIXNUM_BIT) == 0) return C_SCHEME_FALSE;

  x1 = C_unfix(n1);
  x2 = C_unfix(n2);

  if(x2 == 0)
    barf(C_DIVISION_BY_ZERO_ERROR, "fx/?");

#ifdef C_SIXTY_FOUR
  if(x1 == 0x8000000000000000L && x2 == -1) return C_SCHEME_FALSE;
#else
  if(x1 == 0x80000000L && x2 == -1) return C_SCHEME_FALSE;
#endif

  x1 = x1 / x2;

  if(C_fitsinfixnump(x1)) return C_fix(x1);
  else return C_SCHEME_FALSE;
}
