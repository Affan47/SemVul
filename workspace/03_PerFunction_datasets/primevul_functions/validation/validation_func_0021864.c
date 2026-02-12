url_unescape_1 (char *s, unsigned char mask)
{
  char *t = s;
  char *h = s;

  for (; *h; h++, t++)
    {
      if (*h != '%')
        {
        copychar:
          *t = *h;
        }
      else
        {
          char c;

          if (!h[1] || !h[2] || !(c_isxdigit (h[1]) && c_isxdigit (h[2])))
            goto copychar;
          c = X2DIGITS_TO_NUM (h[1], h[2]);
          if (urlchr_test(c, mask))
            goto copychar;


          if (c == '\0')
            goto copychar;
          *t = c;
          h += 2;
        }
    }
  *t = '\0';
}
