cmml_type_find (GstTypeFind * tf, gpointer private)
{

  const guint8 *data = gst_type_find_peek (tf, 0, 12);

  if (data) {


    if (memcmp (data, "CMML\0\0\0\0", 8) != 0)
      return;
    data += 8;


    if (GST_READ_UINT16_LE (data) < 2)
      return;

    gst_type_find_suggest (tf, GST_TYPE_FIND_MAXIMUM, CMML_CAPS);
  }
}
