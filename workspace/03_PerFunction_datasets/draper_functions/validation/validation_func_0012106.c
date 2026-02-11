gst_collect_pads_flush (GstCollectPads * pads, GstCollectData * data,
    guint size)
{
  guint flushsize;
  GstBuffer *buffer;

  g_return_val_if_fail (pads != NULL, 0);
  g_return_val_if_fail (GST_IS_COLLECT_PADS (pads), 0);
  g_return_val_if_fail (data != NULL, 0);


  if ((buffer = data->buffer) == NULL)
    return 0;


  flushsize = MIN (size, GST_BUFFER_SIZE (buffer) - data->pos);

  data->pos += size;

  GST_LOG_OBJECT (pads, "Flushing %d bytes, requested %u", flushsize, size);

  if (data->pos >= GST_BUFFER_SIZE (buffer))

    gst_collect_pads_clear (pads, data);

  return flushsize;
}
