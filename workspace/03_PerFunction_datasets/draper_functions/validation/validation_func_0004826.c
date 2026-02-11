sha512_write (void *context, const void *inbuf_arg, size_t inlen)
{
  const unsigned char *inbuf = inbuf_arg;
  SHA512_CONTEXT *hd = context;

  if (hd->count == 128)
    {
      transform (hd, hd->buf);
      _gcry_burn_stack (768);
      hd->count = 0;
      hd->nblocks++;
    }
  if (!inbuf)
    return;
  if (hd->count)
    {
      for (; inlen && hd->count < 128; inlen--)
	hd->buf[hd->count++] = *inbuf++;
      sha512_write (context, NULL, 0);
      if (!inlen)
	return;
    }

  while (inlen >= 128)
    {
      transform (hd, inbuf);
      hd->count = 0;
      hd->nblocks++;
      inlen -= 128;
      inbuf += 128;
    }
  _gcry_burn_stack (768);
  for (; inlen && hd->count < 128; inlen--)
    hd->buf[hd->count++] = *inbuf++;
}
