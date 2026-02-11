read_data(bgav_stream_t * s)
  {
  char * buffer;
  bgav_packet_t * p;
  vorbis_audio_priv * priv;
  priv = s->data.audio.decoder->priv;
  p = bgav_stream_get_packet_read(s);
  if(!p)
    {
    return 0;
    }

  buffer = ogg_sync_buffer(&priv->dec_oy, p->data_size);
  memcpy(buffer, p->data, p->data_size);
  ogg_sync_wrote(&priv->dec_oy, p->data_size);
  bgav_stream_done_packet_read(s, p);
  return 1;
  }
