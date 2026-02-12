static inline char getSpecialChar(char c) {


  const char *p = specialChars;

  while (p[0] && p[1] != c) {
    p += 2;
  }

  return p[0];
}
