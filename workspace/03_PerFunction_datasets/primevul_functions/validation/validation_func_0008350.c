int blosc_run_decompression_with_context(blosc2_context* context, const void* src, int32_t srcsize,
                                         void* dest, int32_t destsize) {
  int32_t ntbytes;
  uint8_t* _src = (uint8_t*)src;
  uint8_t version;
  int error;

  if (srcsize <= 0) {

    return -1;
  }
  version = _src[0];
  if (version > BLOSC_VERSION_FORMAT) {

    return -1;
  }

  error = initialize_context_decompression(context, src, srcsize, dest, destsize);
  if (error < 0) {
    return error;
  }


  bool memcpyed = context->header_flags & (uint8_t)BLOSC_MEMCPYED;
  if (memcpyed) {

    ntbytes = context->sourcesize;
    int32_t cbytes = sw32_(_src + 12);
    if (ntbytes + BLOSC_MAX_OVERHEAD != cbytes) {
      return -1;
    }

    if (destsize < ntbytes) {
      return -1;
    }
    memcpy(dest, _src + BLOSC_MAX_OVERHEAD, (unsigned int)ntbytes);
  }
  else {

    ntbytes = do_job(context);
    if (ntbytes < 0) {
      return -1;
    }
  }

  assert(ntbytes <= (int32_t)destsize);
  return ntbytes;
}
