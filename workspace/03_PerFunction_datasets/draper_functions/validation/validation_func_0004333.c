my_ismbchar_utf16(CHARSET_INFO *cs __attribute__((unused)),
                  const char *b __attribute__((unused)),
                  const char *e __attribute__((unused)))
{
  if (b + 2 > e)
    return 0;

  if (MY_UTF16_HIGH_HEAD(*b))
  {
    return (b + 4 <= e) && MY_UTF16_LOW_HEAD(b[2]) ? 4 : 0;
  }

  if (MY_UTF16_LOW_HEAD(*b))
    return 0;

  return 2;
}
