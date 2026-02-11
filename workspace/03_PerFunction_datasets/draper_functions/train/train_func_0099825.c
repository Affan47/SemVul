next_packet_wav(bgav_demuxer_context_t * ctx)
  {
  bgav_packet_t * p;
  bgav_stream_t * s;
  wav_priv_t * priv;
  int bytes_to_read;

  priv = ctx->priv;

  s = bgav_track_find_stream(ctx, STREAM_ID);

  if(!s)
    return 1;

  bytes_to_read = priv->packet_size;
  if(ctx->input->position + bytes_to_read >=
     priv->data_start + priv->data_size)
    {
    bytes_to_read = priv->data_start + priv->data_size -
      ctx->input->position;
    }

  if(bytes_to_read <= 0)
    return 0;

  p = bgav_stream_get_packet_write(s);

  p->pts =
    ((ctx->input->position - priv->data_start) * s->data.audio.format.samplerate) /
    (s->codec_bitrate / 8);

  bgav_packet_alloc(p, priv->packet_size);

  p->data_size = bgav_input_read_data(ctx->input, p->data, bytes_to_read);

  PACKET_SET_KEYFRAME(p);

  if(!p->data_size)
    return 0;

  bgav_stream_done_packet_write(s, p);

  return 1;
  }
