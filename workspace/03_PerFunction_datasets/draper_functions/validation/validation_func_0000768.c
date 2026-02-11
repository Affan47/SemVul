bool_char_lconv(char val) {
  switch (val) {
    case 0: return NIL;
    case 1: return T;
    case CHAR_MAX: return S(Kunspecific);
    default:
      pushSTACK(CLSTEXT("~S: localeconv() returned an invalid value ~S (should be one of ~S, ~S, CHAR_MAX=~S)"));
      pushSTACK(TheSubr(subr_self)->name);
      pushSTACK(fixnum(val));
      pushSTACK(Fixnum_0); pushSTACK(Fixnum_1); pushSTACK(fixnum(CHAR_MAX));
      funcall(S(warn),6);
      return fixnum(val);
  }
}
