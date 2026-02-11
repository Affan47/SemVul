gst_value_deserialize_fourcc (GValue * dest, const gchar * s)
{
  gboolean ret = FALSE;
  guint32 fourcc = 0;
  gchar *end;
  gint l = strlen (s);

  if (l == 4) {
    fourcc = GST_MAKE_FOURCC (s[0], s[1], s[2], s[3]);
    ret = TRUE;
  } else if (l == 3) {
    fourcc = GST_MAKE_FOURCC (s[0], s[1], s[2], ' ');
    ret = TRUE;
  } else if (l == 2) {
    fourcc = GST_MAKE_FOURCC (s[0], s[1], ' ', ' ');
    ret = TRUE;
  } else if (l == 1) {
    fourcc = GST_MAKE_FOURCC (s[0], ' ', ' ', ' ');
    ret = TRUE;
  } else if (g_ascii_isdigit (*s)) {
    fourcc = strtoul (s, &end, 0);
    if (*end == 0) {
      ret = TRUE;
    }
  }
  gst_value_set_fourcc (dest, fourcc);

  return ret;
}
