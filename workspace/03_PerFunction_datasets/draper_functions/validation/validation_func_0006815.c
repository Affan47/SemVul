qtdemux_dump_mdhd (GstQTDemux * qtdemux, GstByteReader * data, int depth)
{
  guint32 version = 0;
  guint64 duration, ctime, mtime;
  guint32 time_scale = 0;
  guint16 language = 0, quality = 0;
  guint value_size;

  if (!gst_byte_reader_get_uint32_be (data, &version))
    return FALSE;

  GST_LOG ("%*s  version/flags: %08x", depth, "", version);

  value_size = ((version >> 24) == 1) ? sizeof (guint64) : sizeof (guint32);

  if (qt_atom_parser_get_offset (data, value_size, &ctime) &&
      qt_atom_parser_get_offset (data, value_size, &mtime) &&
      gst_byte_reader_get_uint32_be (data, &time_scale) &&
      qt_atom_parser_get_offset (data, value_size, &duration) &&
      gst_byte_reader_get_uint16_be (data, &language) &&
      gst_byte_reader_get_uint16_be (data, &quality)) {
    GST_LOG ("%*s  creation time: %" G_GUINT64_FORMAT, depth, "", ctime);
    GST_LOG ("%*s  modify time:   %" G_GUINT64_FORMAT, depth, "", mtime);
    GST_LOG ("%*s  time scale:    1/%u sec", depth, "", time_scale);
    GST_LOG ("%*s  duration:      %" G_GUINT64_FORMAT, depth, "", duration);
    GST_LOG ("%*s  language:      %u", depth, "", language);
    GST_LOG ("%*s  quality:       %u", depth, "", quality);
    return TRUE;
  }

  return FALSE;
}
