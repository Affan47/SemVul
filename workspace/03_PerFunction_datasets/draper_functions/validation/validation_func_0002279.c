gst_file_src_query (GstBaseSrc * basesrc, GstQuery * query)
{
  gboolean ret = FALSE;
  GstFileSrc *src = GST_FILE_SRC (basesrc);

  switch (GST_QUERY_TYPE (query)) {
    case GST_QUERY_URI:
      gst_query_set_uri (query, src->uri);
      ret = TRUE;
      break;
    default:
      ret = FALSE;
      break;
  }

  if (!ret)
    ret = GST_BASE_SRC_CLASS (parent_class)->query (basesrc, query);

  return ret;
}
