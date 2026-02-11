gst_pb_utils_get_source_description (const gchar * protocol)
{
  gchar *proto_uc, *ret;

  g_return_val_if_fail (protocol != NULL, NULL);

  if (strcmp (protocol, "cdda") == 0)
    return g_strdup (_("Audio CD source"));

  if (strcmp (protocol, "dvd") == 0)
    return g_strdup (_("DVD source"));

  if (strcmp (protocol, "rtsp") == 0)
    return g_strdup (_("Real Time Streaming Protocol (RTSP) source"));


  if (strcmp (protocol, "mms") == 0)
    return g_strdup (_("Microsoft Media Server (MMS) protocol source"));


  proto_uc = g_ascii_strup (protocol, -1);


  ret = g_strdup_printf (_("%s protocol source"), proto_uc);

  g_free (proto_uc);

  return ret;
}
