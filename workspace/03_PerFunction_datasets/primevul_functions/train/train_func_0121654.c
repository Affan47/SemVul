celt_type_find (GstTypeFind * tf, gpointer private)
{
  const guint8 *data = gst_type_find_peek (tf, 0, 8);

  if (data) {

    if (memcmp (data, "CELT    ", 8) != 0)
      return;


    gst_type_find_suggest (tf, GST_TYPE_FIND_MAXIMUM, CELT_CAPS);
  }
}
