size_t copy_option_part(char_u **option, char_u *buf, size_t maxlen,
                        char *sep_chars)
{
  size_t len = 0;
  char_u  *p = *option;


  if (*p == '.') {
    buf[len++] = *p++;
  }
  while (*p != NUL && vim_strchr((char_u *)sep_chars, *p) == NULL) {

    if (p[0] == '\\' && vim_strchr((char_u *)sep_chars, p[1]) != NULL) {
      p++;
    }
    if (len < maxlen - 1) {
      buf[len++] = *p;
    }
    p++;
  }
  buf[len] = NUL;

  if (*p != NUL && *p != ',') {
    p++;
  }
  p = skip_to_option_part(p);

  *option = p;
  return len;
}
