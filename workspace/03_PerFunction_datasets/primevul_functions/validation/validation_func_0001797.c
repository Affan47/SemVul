int string_copy(char *dst, const char *src, int siz) {
  register char *d = dst;
  register const char *s = src;
  register size_t n = siz;


  if (n != 0 && --n != 0) {
    do {
      if ((*d++ = *s++) == 0)
        break;
    } while (--n != 0);
  }


  if (n == 0) {
    if (siz != 0)
      *d = '\0';
    while (*s++)
      ;
  }

  return(s - src - 1);
}
