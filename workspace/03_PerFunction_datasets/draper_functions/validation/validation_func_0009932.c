resync_file(bgav_demuxer_context_t * ctx,
                       uint8_t * ptr, int offset, int * len)
  {
  int i;
  mpegts_t * priv = ctx->priv;
  uint8_t * ptr1 = ptr + offset + 1;

  int bytes_skipped = 1;

  for(i = 1; i < priv->packet_size; i++)
    {
    if(*ptr1 == 0x47)
      {
      if(*len - offset - bytes_skipped > 0)
        memmove(ptr + offset, ptr1, *len - offset - bytes_skipped);
      *len -= bytes_skipped;
      *len += bgav_input_read_data(ctx->input, ptr + *len, bytes_skipped);
      bgav_log(ctx->opt, BGAV_LOG_INFO, LOG_DOMAIN,
               "Skipped discontinuity %d bytes", bytes_skipped);
      priv->discontinuous = 1;
      return bytes_skipped;
      }
    ptr1++;
    bytes_skipped++;
    }
  return 0;
  }
