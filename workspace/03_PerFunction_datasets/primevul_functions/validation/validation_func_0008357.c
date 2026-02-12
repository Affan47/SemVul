int blosc_compress_context(blosc2_context* context) {
  int ntbytes = 0;
  blosc_timestamp_t last, current;
  bool memcpyed = context->header_flags & (uint8_t)BLOSC_MEMCPYED;

  blosc_set_timestamp(&last);

  if (!memcpyed) {

    ntbytes = do_job(context);
    if (ntbytes < 0) {
      return -1;
    }
    if (ntbytes == 0) {

      context->header_flags |= (uint8_t)BLOSC_MEMCPYED;
      memcpyed = true;
    }
  }

  if (memcpyed) {
    if (context->sourcesize + BLOSC_MAX_OVERHEAD > context->destsize) {

      ntbytes = 0;
    }
    else {
      context->output_bytes = BLOSC_MAX_OVERHEAD;
      ntbytes = do_job(context);
      if (ntbytes < 0) {
        return -1;
      }

      context->dest[2] = context->header_flags;

      context->header_flags &= ~(uint8_t)BLOSC_MEMCPYED;
    }
  }


  _sw32(context->dest + 12, ntbytes);


  context->destsize = ntbytes;

  assert(ntbytes <= context->destsize);

  if (context->btune != NULL) {
    blosc_set_timestamp(&current);
    double ctime = blosc_elapsed_secs(last, current);
    btune_update(context, ctime);
  }

  return ntbytes;
}
