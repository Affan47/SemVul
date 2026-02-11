gst_element_query (GstElement * element, GstQuery * query)
{
  GstElementClass *oclass;
  gboolean result = FALSE;

  g_return_val_if_fail (GST_IS_ELEMENT (element), FALSE);
  g_return_val_if_fail (query != NULL, FALSE);

  oclass = GST_ELEMENT_GET_CLASS (element);

  if (oclass->query) {
    GST_CAT_DEBUG (GST_CAT_ELEMENT_PADS, "send query on element %s",
        GST_ELEMENT_NAME (element));
    result = oclass->query (element, query);
  } else {
    result = gst_element_default_query (element, query);
  }
  return result;
}
