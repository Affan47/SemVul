get_pcm_format(bgav_demuxer_context_t * ctx, bgav_stream_t * s)
  {
  uint8_t  tmp_8;
  uint16_t tmp_16;

  if(!bgav_input_read_8(ctx->input, &tmp_8))
    return 0;
  s->data.audio.bits_per_sample = tmp_8;


  if(!bgav_input_read_8(ctx->input, &tmp_8))
    return 0;
  s->data.audio.format.num_channels = tmp_8;


  if(!bgav_input_read_16_le(ctx->input, &tmp_16))
    return 0;
  s->data.audio.format.samplerate = tmp_16;
  s->data.audio.block_align = (s->data.audio.bits_per_sample * s->data.audio.format.num_channels) / 8;

#if 1
  s->data.audio.bits_per_sample = 8;
  s->data.audio.format.num_channels = 1;
  s->data.audio.format.samplerate /= 4;
#endif
  return 1;
  }
