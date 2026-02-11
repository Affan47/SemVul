gf_wgen_extract_word(gf_t *gf, void *start, int bytes, int index)
{
  uint8_t *ptr;
  uint32_t rv;
  int rs;
  int byte, bit, i;
  gf_internal_t *h;

  h = (gf_internal_t *) gf->scratch;
  rs = bytes / h->w;
  byte = index/8;
  bit = index%8;

  ptr = (uint8_t *) start;
  ptr += bytes;
  ptr -= rs;
  ptr += byte;

  rv = 0;
  for (i = 0; i < h->w; i++) {
    rv <<= 1;
    if ((*ptr) & (1 << bit)) rv |= 1;
    ptr -= rs;
  }

  return rv;
}
