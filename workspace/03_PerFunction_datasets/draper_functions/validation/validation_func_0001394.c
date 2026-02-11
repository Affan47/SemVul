my_string_repertoire(CHARSET_INFO *cs, const char *str, ulong length)
{
  const char *strend= str + length;
  if (cs->mbminlen == 1)
  {
    for ( ; str < strend; str++)
    {
      if (((uchar) *str) > 0x7F)
        return MY_REPERTOIRE_UNICODE30;
    }
  }
  else
  {
    my_wc_t wc;
    int chlen;
    for (;
         (chlen= cs->cset->mb_wc(cs, &wc, (uchar*) str, (uchar*) strend)) > 0;
         str+= chlen)
    {
      if (wc > 0x7F)
        return MY_REPERTOIRE_UNICODE30;
    }
  }
  return MY_REPERTOIRE_ASCII;
}
