safe_snreplace(char *s, size_t sz, const char *pattern, const char *replacement)
{
  char *ptr;
  char *src;
  char *dst;
  size_t num;

  if (!s)
    return -1;

  if (!pattern || !replacement)
    return 0;

  size_t p_len = strlen(pattern);
  size_t r_len = strlen(replacement);
  size_t s_len = strlen(s) + 1;

  ptr = s;
  while ((ptr = strstr(ptr, pattern)))
    {

      src = ptr + p_len;
      dst = ptr + r_len;

      num = s_len - (src - s);
      if (dst + num > s + sz)
	return -1;


      memmove(dst, src, num);


      memcpy(ptr, replacement, r_len);


      ptr = dst;
    }

  return 0;
}
