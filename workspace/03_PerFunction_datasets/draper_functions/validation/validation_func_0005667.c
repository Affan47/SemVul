gst_rdt_manager_request_new_pad (GstElement * element,
    GstPadTemplate * templ, const gchar * name, const GstCaps * caps)
{
  GstRDTManager *rdtmanager;
  GstElementClass *klass;
  GstPad *result;

  g_return_val_if_fail (templ != NULL, NULL);
  g_return_val_if_fail (GST_IS_RDT_MANAGER (element), NULL);

  rdtmanager = GST_RDT_MANAGER (element);
  klass = GST_ELEMENT_GET_CLASS (element);


  if (templ == gst_element_class_get_pad_template (klass, "recv_rtp_sink_%u")) {
    result = create_recv_rtp (rdtmanager, templ, name);
  } else if (templ == gst_element_class_get_pad_template (klass,
          "recv_rtcp_sink_%u")) {
    result = create_recv_rtcp (rdtmanager, templ, name);
  } else if (templ == gst_element_class_get_pad_template (klass, "rtcp_src_%u")) {
    result = create_rtcp (rdtmanager, templ, name);
  } else
    goto wrong_template;

  return result;


wrong_template:
  {
    g_warning ("rdtmanager: this is not our template");
    return NULL;
  }
}
