gst_riff_wave_add_default_channel_mask (GstCaps * caps,
    gint nchannels, gint channel_reorder_map[18])
{
  guint64 channel_mask = 0;
  static const gint reorder_maps[8][11] = {
    {0,},
    {0, 1},
    {-1, -1, -1},
    {0, 1, 2, 3},
    {0, 1, 3, 4, 2},
    {0, 1, 4, 5, 2, 3},
    {-1, -1, -1, -1, -1, -1, -1},
    {0, 1, 4, 5, 2, 3, 6, 7}
  };

  if (nchannels > 8) {
    GST_DEBUG ("invalid number of channels: %d", nchannels);
    return FALSE;
  }


  switch (nchannels) {
    case 1:

      if (channel_reorder_map)
        channel_reorder_map[0] = 0;
      return TRUE;
    case 8:
      channel_mask |=
          G_GUINT64_CONSTANT (1) << GST_AUDIO_CHANNEL_POSITION_SIDE_RIGHT;
      channel_mask |=
          G_GUINT64_CONSTANT (1) << GST_AUDIO_CHANNEL_POSITION_SIDE_LEFT;

    case 6:
      channel_mask |= G_GUINT64_CONSTANT (1) << GST_AUDIO_CHANNEL_POSITION_LFE1;

    case 5:
      channel_mask |=
          G_GUINT64_CONSTANT (1) << GST_AUDIO_CHANNEL_POSITION_FRONT_CENTER;

    case 4:
      channel_mask |=
          G_GUINT64_CONSTANT (1) << GST_AUDIO_CHANNEL_POSITION_REAR_RIGHT;
      channel_mask |=
          G_GUINT64_CONSTANT (1) << GST_AUDIO_CHANNEL_POSITION_REAR_LEFT;

    case 2:
      channel_mask |=
          G_GUINT64_CONSTANT (1) << GST_AUDIO_CHANNEL_POSITION_FRONT_RIGHT;
      channel_mask |=
          G_GUINT64_CONSTANT (1) << GST_AUDIO_CHANNEL_POSITION_FRONT_LEFT;
      break;
    default:
      return FALSE;
  }

  if (channel_reorder_map)
    memcpy (channel_reorder_map, reorder_maps[nchannels - 1],
        sizeof (gint) * nchannels);

  gst_caps_set_simple (caps, "channel-mask", GST_TYPE_BITMASK, channel_mask,
      NULL);

  return TRUE;
}
