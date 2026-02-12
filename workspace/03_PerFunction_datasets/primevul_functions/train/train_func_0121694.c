degas_type_find (GstTypeFind * tf, gpointer private)
{


  gint64 len;
  const guint8 *data;
  guint16 resolution;
  int n;

  len = gst_type_find_get_length (tf);
  if (len < 34)
    return;
  data = gst_type_find_peek (tf, 0, 4);
  if (G_UNLIKELY (data == NULL))
    return;
  resolution = GST_READ_UINT16_BE (data);
  if (len == 32034) {

    if (resolution <= 2)
      gst_type_find_suggest_simple (tf, GST_TYPE_FIND_POSSIBLE + 5,
          "image/x-degas", NULL);
  } else if (len == 32066) {

    if (resolution <= 2) {
      data = gst_type_find_peek (tf, len - 16, 8);
      if (G_UNLIKELY (data == NULL))
        return;
      for (n = 0; n < 4; n++) {
        if (GST_READ_UINT16_BE (data + n * 2) > 2)
          return;
      }
      gst_type_find_suggest_simple (tf, GST_TYPE_FIND_POSSIBLE + 5,
          "image/x-degas", NULL);
    }
  } else if (len >= 66 && len < 32066) {


    if ((resolution & 0x8000) && (resolution & 0x7fff) <= 2) {
      data = gst_type_find_peek (tf, len - 16, 8);
      if (G_UNLIKELY (data == NULL))
        return;
      for (n = 0; n < 4; n++) {
        if (GST_READ_UINT16_BE (data + n * 2) > 2)
          return;
      }
      gst_type_find_suggest_simple (tf, GST_TYPE_FIND_POSSIBLE + 5,
          "image/x-degas", NULL);
    }
  }
}
