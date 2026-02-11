lj_cconv_ct_init(CTState *cts, CType *d, CTSize sz,
		      uint8_t *dp, TValue *o, MSize len)
{
  if (len == 0)
    memset(dp, 0, sz);
  else if (len == 1 && !lj_cconv_multi_init(cts, d, o))
    lj_cconv_ct_tv(cts, d, dp, o, 0);
  else if (ctype_isarray(d->info))
    cconv_array_init(cts, d, sz, dp, o, len);
  else if (ctype_isstruct(d->info))
    cconv_struct_init(cts, d, sz, dp, o, len);
  else
    cconv_err_initov(cts, d);
}
