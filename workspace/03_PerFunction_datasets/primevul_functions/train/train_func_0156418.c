qtdemux_parse_amr_bitrate (GstBuffer * buf, gboolean wb)
{


  static const guint nb_bitrates[] = {
    4750, 5150, 5900, 6700, 7400, 7950, 10200, 12200
  };
  static const guint wb_bitrates[] = {
    6600, 8850, 12650, 14250, 15850, 18250, 19850, 23050, 23850
  };
  GstMapInfo map;
  gsize max_mode;
  guint16 mode_set;

  gst_buffer_map (buf, &map, GST_MAP_READ);

  if (map.size != 0x11) {
    GST_DEBUG ("Atom should have size 0x11, not %" G_GSIZE_FORMAT, map.size);
    goto bad_data;
  }

  if (QT_FOURCC (map.data + 4) != FOURCC_damr) {
    GST_DEBUG ("Unknown atom in %" GST_FOURCC_FORMAT,
        GST_FOURCC_ARGS (QT_UINT32 (map.data + 4)));
    goto bad_data;
  }

  mode_set = QT_UINT16 (map.data + 13);

  if (mode_set == (wb ? AMR_WB_ALL_MODES : AMR_NB_ALL_MODES))
    max_mode = 7 + (wb ? 1 : 0);
  else

    max_mode = g_bit_nth_msf ((gulong) mode_set & (wb ? 0x1ff : 0xff), -1);

  if (max_mode == -1) {
    GST_DEBUG ("No mode indication was found (mode set) = %x",
        (guint) mode_set);
    goto bad_data;
  }

  gst_buffer_unmap (buf, &map);
  return wb ? wb_bitrates[max_mode] : nb_bitrates[max_mode];

bad_data:
  gst_buffer_unmap (buf, &map);
  return 0;
}
