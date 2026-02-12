gst_aac_parse_get_audio_channel_configuration (gint num_channels)
{
  if (num_channels >= 1 && num_channels <= 6)
    return (guint8) num_channels;
  else if (num_channels == 8)
    return (guint8) 7U;
  else
    return G_MAXUINT8;


}
