b64_decode(int *dstlen, const char *src)
{
  uint8_t *out;
  int len;
  int ret;

  len = AV_BASE64_DECODE_SIZE(strlen(src));


  CHECK_NULL(L_MISC, out = calloc(1, len + 1));

  ret = av_base64_decode(out, src, len);
  if (ret < 0)
    {
      free(out);
      return NULL;
    }

  if (dstlen)
    *dstlen = ret;

  return out;
}
