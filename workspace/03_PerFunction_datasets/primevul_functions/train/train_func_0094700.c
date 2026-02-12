static char unescapeChar(char c) {


  const char *p = specialChars + 4;

  for (;;) {
    if (p[0] == '\0') return c;
    if (p[0] == c) return p[1];
    p += 2;
  }
}
