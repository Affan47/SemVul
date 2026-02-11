est_inflate(const char *ptr, int size, int *sp, int mode){
#if ESTUSEZLIB
  z_stream zs;
  char *buf;
  unsigned char obuf[ESTIOBUFSIZ];
  int rv, asiz, bsiz, osiz;
  zs.zalloc = Z_NULL;
  zs.zfree = Z_NULL;
  zs.opaque = Z_NULL;
  switch(mode){
  case -1:
    if(inflateInit2(&zs, -15) != Z_OK) return NULL;
    break;
  case 1:
    if(inflateInit2(&zs, 15 + 16) != Z_OK) return NULL;
    break;
  default:
    if(inflateInit2(&zs, 15) != Z_OK) return NULL;
    break;
  }
  asiz = size * 2 + 16;
  if(asiz < ESTIOBUFSIZ) asiz = ESTIOBUFSIZ;
  CB_MALLOC(buf, asiz);
  bsiz = 0;
  zs.next_in = (unsigned char *)ptr;
  zs.avail_in = size;
  zs.next_out = obuf;
  zs.avail_out = ESTIOBUFSIZ;
  while((rv = inflate(&zs, Z_NO_FLUSH)) == Z_OK){
    osiz = ESTIOBUFSIZ - zs.avail_out;
    if(bsiz + osiz >= asiz){
      asiz = asiz * 2 + osiz;
      CB_REALLOC(buf, asiz);
    }
    memcpy(buf + bsiz, obuf, osiz);
    bsiz += osiz;
    zs.next_out = obuf;
    zs.avail_out = ESTIOBUFSIZ;
  }
  if(rv != Z_STREAM_END){
    free(buf);
    inflateEnd(&zs);
    return NULL;
  }
  osiz = ESTIOBUFSIZ - zs.avail_out;
  if(bsiz + osiz >= asiz){
    asiz = asiz * 2 + osiz;
    CB_REALLOC(buf, asiz);
  }
  memcpy(buf + bsiz, obuf, osiz);
  bsiz += osiz;
  buf[bsiz] = '\0';
  if(sp) *sp = bsiz;
  inflateEnd(&zs);
  return buf;
#else
  if(sp) *sp = size;
  return cbmemdup(ptr, size);
#endif
}
