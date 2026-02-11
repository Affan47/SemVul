my_casedn_8bit(CHARSET_INFO * cs, char *src, size_t srclen,
                      char *dst __attribute__((unused)),
                      size_t dstlen __attribute__((unused)))
{
  char *end= src + srclen;
  register uchar *map=cs->to_lower;
  DBUG_ASSERT(src == dst && srclen == dstlen);
  for ( ; src != end ; src++)
    *src= (char) map[(uchar) *src];
  return srclen;
}
