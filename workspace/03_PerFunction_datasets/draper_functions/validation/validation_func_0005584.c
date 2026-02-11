gst_cdxa_parse_sync (GstBuffer * buf)
{
  const guint8 sync_marker[12] = { 0x00, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
    0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x00
  };
  guint8 *data;
  guint size;

  size = GST_BUFFER_SIZE (buf);
  data = GST_BUFFER_DATA (buf);

  while (size >= 12) {
    if (memcmp (data, sync_marker, 12) == 0) {
      return (gint) (data - GST_BUFFER_DATA (buf));
    }
    --size;
    ++data;
  }
  return -1;
}
