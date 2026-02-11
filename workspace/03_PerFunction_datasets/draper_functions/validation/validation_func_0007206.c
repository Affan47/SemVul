constant (pTHX_ const char *name, STRLEN len, IV *iv_return) {


  switch (len) {
  case 18:
    if (memEQ(name, "NETSNMP_DS_MAX_IDS", 18)) {
#ifdef NETSNMP_DS_MAX_IDS
      *iv_return = NETSNMP_DS_MAX_IDS;
      return PERL_constant_ISIV;
#else
      return PERL_constant_NOTDEF;
#endif
    }
    break;
  case 19:
    if (memEQ(name, "NETSNMP_DS_TOKEN_ID", 19)) {
#ifdef NETSNMP_DS_TOKEN_ID
      *iv_return = NETSNMP_DS_TOKEN_ID;
      return PERL_constant_ISIV;
#else
      return PERL_constant_NOTDEF;
#endif
    }
    break;
  case 21:


    switch (name[11]) {
    case 'L':
      if (memEQ(name, "NETSNMP_DS_LIBRARY_ID", 21)) {

#ifdef NETSNMP_DS_LIBRARY_ID
        *iv_return = NETSNMP_DS_LIBRARY_ID;
        return PERL_constant_ISIV;
#else
        return PERL_constant_NOTDEF;
#endif
      }
      break;
    case 'M':
      if (memEQ(name, "NETSNMP_DS_MAX_SUBIDS", 21)) {

#ifdef NETSNMP_DS_MAX_SUBIDS
        *iv_return = NETSNMP_DS_MAX_SUBIDS;
        return PERL_constant_ISIV;
#else
        return PERL_constant_NOTDEF;
#endif
      }
      break;
    }
    break;
  case 22:
    return constant_22 (aTHX_ name, iv_return);
    break;
  case 23:
    return constant_23 (aTHX_ name, iv_return);
    break;
  case 24:
    return constant_24 (aTHX_ name, iv_return);
    break;
  case 25:
    return constant_25 (aTHX_ name, iv_return);
    break;
  case 26:
    return constant_26 (aTHX_ name, iv_return);
    break;
  case 27:
    return constant_27 (aTHX_ name, iv_return);
    break;
  case 28:
    return constant_28 (aTHX_ name, iv_return);
    break;
  case 29:
    return constant_29 (aTHX_ name, iv_return);
    break;
  case 30:
    return constant_30 (aTHX_ name, iv_return);
    break;
  case 31:
    return constant_31 (aTHX_ name, iv_return);
    break;
  case 32:
    return constant_32 (aTHX_ name, iv_return);
    break;
  case 33:
    return constant_33 (aTHX_ name, iv_return);
    break;
  case 34:
    return constant_34 (aTHX_ name, iv_return);
    break;
  case 35:
    if (memEQ(name, "NETSNMP_DS_LIB_STRING_OUTPUT_FORMAT", 35)) {
#ifdef NETSNMP_DS_LIB_STRING_OUTPUT_FORMAT
      *iv_return = NETSNMP_DS_LIB_STRING_OUTPUT_FORMAT;
      return PERL_constant_ISIV;
#else
      return PERL_constant_NOTDEF;
#endif
    }
    break;
  case 38:
    return constant_38 (aTHX_ name, iv_return);
    break;
  }
  return PERL_constant_NOTFOUND;
}
