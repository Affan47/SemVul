SWIG_From_unsigned_SS_long_SS_long  SWIG_PERL_DECL_ARGS_1(unsigned long long value)
{
  SV *sv;
  if (value <= UV_MAX)
    sv = newSVuv((UV)(value));
  else {

    char temp[256];
    sprintf(temp, "%llu", value);
    sv = newSVpv(temp, 0);
  }
  return sv_2mortal(sv);
}
