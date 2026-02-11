C_i_o_fixnum_ior(C_word n1, C_word n2)
{
  C_uword x1, x2, r;

  if((n1 & C_FIXNUM_BIT) == 0 || (n2 & C_FIXNUM_BIT) == 0) return C_SCHEME_FALSE;

  x1 = C_unfix(n1);
  x2 = C_unfix(n2);
  r = x1 | x2;

  if(((r & C_INT_SIGN_BIT) >> 1) != (r & C_INT_TOP_BIT)) return C_SCHEME_FALSE;
  else return C_fix(r);
}
