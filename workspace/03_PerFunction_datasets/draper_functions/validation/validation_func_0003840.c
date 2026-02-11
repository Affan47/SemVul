Curl_getASN1Element(curl_asn1Element * elem,
                                 const char * beg, const char * end)
{
  unsigned char b;
  unsigned long len;
  curl_asn1Element lelem;


  if(beg >= end || !*beg)
    return (const char *) NULL;


  b = (unsigned char) *beg++;
  elem->constructed = (b & 0x20) != 0;
  elem->class = (b >> 6) & 3;
  b &= 0x1F;
  if(b == 0x1F)
    return (const char *) NULL;
  elem->tag = b;


  if(beg >= end)
    return (const char *) NULL;
  b = (unsigned char) *beg++;
  if(!(b & 0x80))
    len = b;
  else if(!(b &= 0x7F)) {


    if(!elem->constructed)
      return (const char *) NULL;
    elem->beg = beg;
    while(beg < end && *beg) {
      beg = Curl_getASN1Element(&lelem, beg, end);
      if(!beg)
        return (const char *) NULL;
    }
    if(beg >= end)
      return (const char *) NULL;
    elem->end = beg;
    return beg + 1;
  }
  else if(beg + b > end)
    return (const char *) NULL;
  else {

    len = 0;
    do {
      if(len & 0xFF000000L)
        return (const char *) NULL;
      len = (len << 8) | (unsigned char) *beg++;
    } while(--b);
  }
  if((unsigned long) (end - beg) < len)
    return (const char *) NULL;
  elem->beg = beg;
  elem->end = beg + len;
  return elem->end;
}
