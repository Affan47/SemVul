gf_w8_shift_multiply (gf_t *gf, uint32_t a8, uint32_t b8)
{
  uint16_t product, i, pp, a, b;
  gf_internal_t *h;

  a = a8;
  b = b8;
  h = (gf_internal_t *) gf->scratch;
  pp = h->prim_poly;

  product = 0;

  for (i = 0; i < GF_FIELD_WIDTH; i++) {
    if (a & (1 << i)) product ^= (b << i);
  }
  for (i = (GF_FIELD_WIDTH*2-2); i >= GF_FIELD_WIDTH; i--) {
    if (product & (1 << i)) product ^= (pp << (i-GF_FIELD_WIDTH));
  }
  return product;
}
