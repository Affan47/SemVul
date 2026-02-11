check_tag(char *from, const char *tag) {
  char *a = from + 1;
  int i = 0;
  char s[256];

  while(is_space(*a))
    a++;
  while((isalnum((unsigned char) *a) || (*a == '/')) && (i < 250)) {
    s[i++] = *a;
    a++;
  }
  s[i++] = '\0';
  return (strfield2(s, tag));
}
