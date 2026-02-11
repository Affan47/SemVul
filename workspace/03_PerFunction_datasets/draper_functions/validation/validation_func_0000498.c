cleanup_stream_ffmpeg(bgav_stream_t * s)
  {
  if(s->type == BGAV_STREAM_VIDEO)
    {
    if(s->priv)
      free(s->priv);
    }
  }
