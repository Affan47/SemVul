gst_tag_xmp_writer_remove_schema (GstTagXmpWriter * config,
    const gchar * schema)
{
  GstTagXmpWriterData *data;
  GSList *iter = NULL;

  g_return_if_fail (GST_IS_TAG_XMP_WRITER (config));

  data = gst_tag_xmp_writer_get_data (config);

  GST_TAG_XMP_WRITER_DATA_LOCK (data);
  for (iter = data->schemas; iter; iter = g_slist_next (iter)) {
    if (strcmp ((const gchar *) iter->data, schema) == 0) {
      g_free (iter->data);
      data->schemas = g_slist_delete_link (data->schemas, iter);
      break;
    }
  }
  GST_TAG_XMP_WRITER_DATA_UNLOCK (data);
}
