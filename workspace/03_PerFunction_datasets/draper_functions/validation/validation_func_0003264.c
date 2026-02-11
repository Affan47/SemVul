gst_rtp_base_depayload_push_list (GstRTPBaseDepayload * filter,
    GstBufferList * out_list)
{
  GstFlowReturn res;

  res = gst_rtp_base_depayload_prepare_push (filter, TRUE, &out_list);

  if (G_LIKELY (res == GST_FLOW_OK))
    res = gst_pad_push_list (filter->srcpad, out_list);
  else
    gst_buffer_list_unref (out_list);

  return res;
}
