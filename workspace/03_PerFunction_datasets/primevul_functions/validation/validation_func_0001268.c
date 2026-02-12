static char * __cvt(double value, int ndigit, int *decpt, int *sign,
                    int fmode, int pad) {
  register char *s = nullptr;
  char *p, *rve, c;
  size_t siz;

  if (ndigit < 0) {
    siz = -ndigit + 1;
  } else {
    siz = ndigit + 1;
  }


  if (value == 0.0) {
    *decpt = 1 - fmode;
    *sign = 0;
    if ((rve = s = (char *)malloc(ndigit?siz:2)) == nullptr) {
      return(nullptr);
    }
    *rve++ = '0';
    *rve = '\0';
    if (!ndigit) {
      return(s);
    }
  } else {
    p = zend_dtoa(value, fmode + 2, ndigit, decpt, sign, &rve);
    if (*decpt == 9999) {

      *decpt = 0;
      c = *p;
      zend_freedtoa(p);
      return strdup(c == 'I' ? "INF" : "NAN");
    }

    if (pad && fmode) {
      siz += *decpt;
    }
    if ((s = (char *)malloc(siz+1)) == nullptr) {
      zend_freedtoa(p);
      return(nullptr);
    }
    (void)string_copy(s, p, siz);
    rve = s + (rve - p);
    zend_freedtoa(p);
  }


  if (pad) {
    siz -= rve - s;
    while (--siz) {
      *rve++ = '0';
    }
    *rve = '\0';
  }

  return(s);
}
