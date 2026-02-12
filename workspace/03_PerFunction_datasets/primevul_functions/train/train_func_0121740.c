ssa_type_find (GstTypeFind * tf, gpointer private)
{
  const gchar *start, *end, *ver_str, *media_type = NULL;
  const guint8 *data;
  gchar *str, *script_type, *p = NULL;
  gint64 len;

  data = gst_type_find_peek (tf, 0, 32);

  if (data == NULL)
    return;


  if (memcmp (data, "[Script Info]", 13) != 0 &&
      memcmp (data + 3, "[Script Info]", 13) != 0) {
    return;
  }


  len = gst_type_find_get_length (tf);
  if (len > 8192)
    len = 8192;

  data = gst_type_find_peek (tf, 0, len);
  if (data == NULL)
    return;


  start = (gchar *) memchr (data, '[', 5);
  g_assert (start);
  len -= (start - (gchar *) data);


  if (!g_utf8_validate (start, len, &end) && (len - (end - start)) > 6) {
    GST_FIXME ("non-UTF8 SSA/ASS file");
    return;
  }


  if (data[0] != '[' && (data[0] != 0xEF || data[1] != 0xBB || data[2] != 0xBF))
    return;


  len = end - start;


  str = g_strndup (start, len - 1);
  script_type = strstr (str, "ScriptType:");
  if (script_type != NULL) {
    gdouble version;

    ver_str = script_type + 11;
    while (*ver_str == ' ' || *ver_str == 'v' || *ver_str == 'V')
      ++ver_str;
    version = g_ascii_strtod (ver_str, &p);
    if (version == 4.0 && p != NULL && *p == '+')
      media_type = "application/x-ass";
    else if (version >= 1.0 && version <= 4.0)
      media_type = "application/x-ssa";
  }

  if (media_type == NULL) {
    if (strstr (str, "[v4+ Styles]") || strstr (str, "[V4+ Styles]"))
      media_type = "application/x-ass";
    else if (strstr (str, "[v4 Styles]") || strstr (str, "[V4 Styles]"))
      media_type = "application/x-ssa";
  }

  if (media_type != NULL) {
    gst_type_find_suggest_simple (tf, GST_TYPE_FIND_MAXIMUM,
        media_type, "parsed", G_TYPE_BOOLEAN, FALSE, NULL);
  } else {
    GST_WARNING ("could not detect SSA/ASS variant");
  }

  g_free (str);
}
