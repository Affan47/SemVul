to_ascii(CHARSET_INFO *cs,
         const char *src, uint src_length,
         char *dst, uint dst_length)

{
  int cnvres;
  my_wc_t wc;
  const char *srcend= src + src_length;
  char *dst0= dst, *dstend= dst + dst_length - 1;
  while (dst < dstend &&
         (cnvres= (cs->cset->mb_wc)(cs, &wc,
                                    (const uchar*) src,
                                    (const uchar*) srcend)) > 0 &&
         wc < 128)
  {
    src+= cnvres;
    *dst++= wc;
  }
  *dst= '\0';
  return dst - dst0;
}
