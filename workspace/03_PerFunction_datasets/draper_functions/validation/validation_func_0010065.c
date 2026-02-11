gst_mpd_client_set_segment_index_for_all_streams (GstMpdClient * client,
    guint segment_idx)
{
  GList *list;

  g_return_if_fail (client != NULL);
  g_return_if_fail (client->active_streams != NULL);


  for (list = g_list_first (client->active_streams); list;
      list = g_list_next (list)) {
    GstActiveStream *stream = (GstActiveStream *) list->data;
    if (stream) {
      stream->segment_idx = segment_idx;
    }
  }
}
