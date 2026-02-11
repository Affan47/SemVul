gst_iterator_new (guint size,
    GType type,
    GMutex * lock,
    guint32 * master_cookie,
    GstIteratorCopyFunction copy,
    GstIteratorNextFunction next,
    GstIteratorItemFunction item,
    GstIteratorResyncFunction resync, GstIteratorFreeFunction free)
{
  GstIterator *result;

  g_return_val_if_fail (size >= sizeof (GstIterator), NULL);
  g_return_val_if_fail (g_type_qname (type) != 0, NULL);
  g_return_val_if_fail (master_cookie != NULL, NULL);
  g_return_val_if_fail (next != NULL, NULL);
  g_return_val_if_fail (resync != NULL, NULL);
  g_return_val_if_fail (free != NULL, NULL);

  result = g_slice_alloc0 (size);
  gst_iterator_init (result, size, type, lock, master_cookie, copy, next, item,
      resync, free);

  return result;
}
