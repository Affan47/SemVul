gst_auto_convert_get_element_by_type (GstAutoConvert * autoconvert, GType type)
{
  GstIterator *iter = NULL;
  GstElement *elem = NULL;
  gboolean done;

  g_return_val_if_fail (type != 0, NULL);

  iter = gst_bin_iterate_elements (GST_BIN (autoconvert));

  if (!iter)
    return NULL;

  done = FALSE;
  while (!done) {
    switch (gst_iterator_next (iter, (gpointer) & elem)) {
      case GST_ITERATOR_OK:
        if (G_OBJECT_TYPE (elem) == type)
          done = TRUE;
        else
          gst_object_unref (elem);
        break;
      case GST_ITERATOR_RESYNC:
        gst_iterator_resync (iter);
        elem = NULL;
        break;
      case GST_ITERATOR_ERROR:
        GST_ERROR ("Error iterating elements in bin");
        elem = NULL;
        done = TRUE;
        break;
      case GST_ITERATOR_DONE:
        elem = NULL;
        done = TRUE;
        break;
    }
  }
  gst_iterator_free (iter);

  return elem;
}
