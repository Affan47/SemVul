int mg_base64_final(char *to, int n) {
  int saved = n;

  if (n & 3) n = mg_base64_update(0, to, n);
  if ((saved & 3) == 2) n--;

  while (n & 3) to[n++] = '=';
  to[n] = '\0';
  return n;
}
