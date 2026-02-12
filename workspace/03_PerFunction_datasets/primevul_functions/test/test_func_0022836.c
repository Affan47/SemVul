int my_wc_mb_utf8_with_escape(CHARSET_INFO *cs, my_wc_t escape, my_wc_t wc,
                              uchar *str, uchar *end)
{
  DBUG_ASSERT(escape > 0);
  if (str + 1 >= end)
    return MY_CS_TOOSMALL2;
  *str= (uchar)escape;
  int cnvres= my_charset_utf8_handler.wc_mb(cs, wc, str + 1, end);
  if (cnvres > 0)
    return cnvres + 1;
  if (cnvres == MY_CS_ILUNI)
    return MY_CS_ILUNI;
  DBUG_ASSERT(cnvres <= MY_CS_TOOSMALL);
  return cnvres - 1;
}
