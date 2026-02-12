static int qp_decode_triple (char *s, char *d)
{

  if (*s == '=' && !(*(s+1)))
    return 1;


  if (*s == '=' &&
      isxdigit ((unsigned char) *(s+1)) &&
      isxdigit ((unsigned char) *(s+2)))
  {
    *d = (hexval (*(s+1)) << 4) | hexval (*(s+2));
    return 0;
  }


  return -1;
}
