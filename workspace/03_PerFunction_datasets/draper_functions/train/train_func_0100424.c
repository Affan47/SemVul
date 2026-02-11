rtp_source_finalize (GObject * object)
{
  RTPSource *src;
  GstBuffer *buffer;

  src = RTP_SOURCE_CAST (object);

  while ((buffer = g_queue_pop_head (src->packets)))
    gst_buffer_unref (buffer);
  g_queue_free (src->packets);

  gst_structure_free (src->sdes);

  g_free (src->bye_reason);

  gst_caps_replace (&src->caps, NULL);

  g_list_foreach (src->conflicting_addresses, (GFunc) g_free, NULL);
  g_list_free (src->conflicting_addresses);

  while ((buffer = g_queue_pop_head (src->retained_feedback)))
    gst_buffer_unref (buffer);
  g_queue_free (src->retained_feedback);

  G_OBJECT_CLASS (rtp_source_parent_class)->finalize (object);
}
