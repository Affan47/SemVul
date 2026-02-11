gst_multi_fd_sink_client_queue_data (GstMultiFdSink * sink,
    GstTCPClient * client, gchar * data, gint len)
{
  GstBuffer *buf;

  buf = gst_buffer_new ();
  GST_BUFFER_DATA (buf) = (guint8 *) data;
  GST_BUFFER_MALLOCDATA (buf) = (guint8 *) data;
  GST_BUFFER_SIZE (buf) = len;

  GST_LOG_OBJECT (sink, "[fd %5d] queueing data of length %d",
      client->fd.fd, len);

  client->sending = g_slist_append (client->sending, buf);

  return TRUE;
}
