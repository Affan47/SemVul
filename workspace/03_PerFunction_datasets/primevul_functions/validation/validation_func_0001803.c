static struct gfxinfo *php_handle_swc(const req::ptr<File>& stream) {
  struct gfxinfo *result = nullptr;

  long bits;
  unsigned long len=64, szlength;
  int factor=1,maxfactor=16;
  int slength, status=0;
  unsigned char *b, *buf=nullptr;
  String bufz;
  String tmp;

  b = (unsigned char *)IM_CALLOC(1, len + 1);
  CHECK_ALLOC_R(b, (len + 1), nullptr);

  if (!stream->seek(5, SEEK_CUR)) {
    IM_FREE(b);
    return nullptr;
  }

  String a = stream->read(64);
  if (a.length() != 64) {
    IM_FREE(b);
    return nullptr;
  }

  if (uncompress((Bytef*)b, &len, (const Bytef*)a.c_str(), 64) != Z_OK) {

    if (!stream->seek(8, SEEK_SET)) {
      IM_FREE(b);
      return nullptr;
    }

    while (!(tmp = stream->read(8192)).empty()) {
      bufz += tmp;
    }
    slength = bufz.length();


    do {
      szlength=slength*(1<<factor++);
      buf = (unsigned char *) IM_REALLOC(buf,szlength);
      if (!buf) IM_FREE(b);
      CHECK_ALLOC_R(buf, szlength, nullptr);
      status = uncompress((Bytef*)buf, &szlength,
                          (const Bytef*)bufz.c_str(), slength);
    } while ((status==Z_BUF_ERROR)&&(factor<maxfactor));

    if (status == Z_OK) {
       memcpy(b, buf, len);
    }

    if (buf) {
      IM_FREE(buf);
    }
  }

  if (!status) {
    result = (struct gfxinfo *)IM_CALLOC(1, sizeof (struct gfxinfo));
    if (!result) IM_FREE(b);
    CHECK_ALLOC_R(result, sizeof (struct gfxinfo), nullptr);
    bits = php_swf_get_bits (b, 0, 5);
    result->width = (php_swf_get_bits (b, 5 + bits, bits) -
      php_swf_get_bits (b, 5, bits)) / 20;
    result->height = (php_swf_get_bits (b, 5 + (3 * bits), bits) -
      php_swf_get_bits (b, 5 + (2 * bits), bits)) / 20;
  } else {
    result = nullptr;
  }

  IM_FREE(b);
  return result;
}
