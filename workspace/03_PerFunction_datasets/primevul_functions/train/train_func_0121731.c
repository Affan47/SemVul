speex_type_find (GstTypeFind * tf, gpointer private)
{
  const guint8 *data = gst_type_find_peek (tf, 0, 80);

  if (data) {


    if (memcmp (data, "Speex   ", 8) != 0)
      return;
    data += 32;


    if (GST_READ_UINT32_LE (data) < 80)
      return;
    data += 4;


    if (GST_READ_UINT32_LE (data) > 48000)
      return;
    data += 4;


    if (GST_READ_UINT32_LE (data) > 3)
      return;
    data += 12;

    gst_type_find_suggest (tf, GST_TYPE_FIND_MAXIMUM, SPEEX_CAPS);
  }
}
