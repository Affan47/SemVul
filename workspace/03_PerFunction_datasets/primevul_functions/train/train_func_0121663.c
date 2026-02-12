dvdiso_type_find (GstTypeFind * tf, gpointer private)
{

  gint64 len;
  const guint8 *data;

  len = gst_type_find_get_length (tf);
  if (len < 0x8006)
    return;
  data = gst_type_find_peek (tf, 0, 0x8006);
  if (G_UNLIKELY (data == NULL))
    return;
  for (len = 0; len < 0x8000; len++)
    if (data[len])
      return;

  if (memcmp (data + 0x8000, "\001CD001", 6))
    return;


  gst_type_find_suggest_simple (tf, GST_TYPE_FIND_LIKELY,
      "application/octet-stream", NULL);
}
