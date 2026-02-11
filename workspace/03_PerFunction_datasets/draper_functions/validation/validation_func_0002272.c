gst_adapter_take_list (GstAdapter * adapter, gsize nbytes)
{
  GQueue queue = G_QUEUE_INIT;
  GstBuffer *cur;
  gsize hsize, skip;

  g_return_val_if_fail (GST_IS_ADAPTER (adapter), NULL);
  g_return_val_if_fail (nbytes <= adapter->size, NULL);

  GST_LOG_OBJECT (adapter, "taking %" G_GSIZE_FORMAT " bytes", nbytes);

  while (nbytes > 0) {
    cur = adapter->buflist->data;
    skip = adapter->skip;
    hsize = MIN (nbytes, gst_buffer_get_size (cur) - skip);

    cur = gst_adapter_take_buffer (adapter, hsize);

    g_queue_push_tail (&queue, cur);

    nbytes -= hsize;
  }
  return queue.head;
}
