gst_adapter_push (GstAdapter * adapter, GstBuffer * buf)
{
  guint size;

  g_return_if_fail (GST_IS_ADAPTER (adapter));
  g_return_if_fail (GST_IS_BUFFER (buf));

  size = GST_BUFFER_SIZE (buf);
  adapter->size += size;


  if (G_UNLIKELY (adapter->buflist == NULL)) {
    GST_LOG_OBJECT (adapter, "pushing first %u bytes", size);
    adapter->buflist = adapter->buflist_end = g_slist_append (NULL, buf);
    update_timestamp (adapter, buf);
  } else {

    GST_LOG_OBJECT (adapter, "pushing %u bytes at end, size now %u", size,
        adapter->size);
    adapter->buflist_end = g_slist_append (adapter->buflist_end, buf);
    adapter->buflist_end = g_slist_next (adapter->buflist_end);
  }
}
