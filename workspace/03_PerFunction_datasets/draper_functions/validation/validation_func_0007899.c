gst_query_finalize (GstQuery * query)
{
  g_return_if_fail (query != NULL);

  if (query->structure) {
    gst_structure_set_parent_refcount (query->structure, NULL);
    gst_structure_free (query->structure);
  }


}
