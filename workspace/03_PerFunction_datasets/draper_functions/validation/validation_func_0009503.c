gst_m3u8_entry_new (const gchar * url, GFile * file, const gchar * title,
    gfloat duration, gboolean discontinuous)
{
  GstM3U8Entry *entry;

  g_return_val_if_fail (url != NULL, NULL);
  g_return_val_if_fail (title != NULL, NULL);

  entry = g_new0 (GstM3U8Entry, 1);
  entry->url = g_strdup (url);
  entry->title = g_strdup (title);
  entry->duration = duration;
  entry->file = file;
  entry->discontinuous = discontinuous;
  return entry;
}
