init_format(bgav_stream_t * s)
  {
  ffmpeg_audio_priv * priv;
  priv= s->data.audio.decoder->priv;


  s->data.audio.format.num_channels = priv->ctx->channels;
  s->data.audio.format.samplerate   = priv->ctx->sample_rate;


  s->data.audio.format.sample_format =
    sample_format_ffmpeg_2_gavl(priv->ctx->sample_fmt);


  if(s->data.audio.format.sample_format == GAVL_SAMPLE_NONE)
    {
    bgav_log(s->opt, BGAV_LOG_ERROR, LOG_DOMAIN,
             "Could not get sample format (maybe codec init failed)");
      return 0;
    }
  priv->sample_size =
    gavl_bytes_per_sample(s->data.audio.format.sample_format);

  gavl_set_channel_setup(&s->data.audio.format);

#ifndef DECODE_AUDIO4
  s->data.audio.format.samples_per_frame = 2*AVCODEC_MAX_AUDIO_FRAME_SIZE;
  priv->frame = gavl_audio_frame_create(&s->data.audio.format);
  priv->frame_alloc =
    priv->sample_size *
    s->data.audio.format.num_channels *
    s->data.audio.format.samples_per_frame;
  s->data.audio.format.samples_per_frame = 1024;
#endif


  return 1;
  }
