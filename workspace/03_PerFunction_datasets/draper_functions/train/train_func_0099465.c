pvariable(char **fmt, char *buf)
{
  char *start=*fmt;
  char c;
  int len;

  while (1) {
    c = *(*fmt)++;
    if (isalnum((int) c) || (c == '_'))
      continue;
    else
      break;
  }
  (*fmt)--;
  len = *fmt - start;
  memcpy(buf, start, len);
  buf[len] = 0;

  return buf;

}
