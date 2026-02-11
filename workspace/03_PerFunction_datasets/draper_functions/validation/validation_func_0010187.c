gst_element_send_event (GstElement * element, GstEvent * event)
{
  GstElementClass *oclass;
  gboolean result = FALSE;

  g_return_val_if_fail (GST_IS_ELEMENT (element), FALSE);
  g_return_val_if_fail (event != NULL, FALSE);

  oclass = GST_ELEMENT_GET_CLASS (element);

  GST_STATE_LOCK (element);
  if (oclass->send_event) {
    GST_CAT_DEBUG (GST_CAT_ELEMENT_PADS, "send %s event on element %s",
        GST_EVENT_TYPE_NAME (event), GST_ELEMENT_NAME (element));
    result = oclass->send_event (element, event);
  }
  GST_STATE_UNLOCK (element);

  return result;
}
