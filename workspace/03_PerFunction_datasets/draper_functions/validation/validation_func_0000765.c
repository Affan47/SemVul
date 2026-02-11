gst_curl_base_sink_data_sent_notify (GstCurlBaseSink * sink)
{
  GST_LOG ("transfer completed");
  GST_OBJECT_LOCK (sink);
  sink->transfer_cond->data_available = FALSE;
  sink->transfer_cond->data_sent = TRUE;
  g_cond_signal (&sink->transfer_cond->cond);
  GST_OBJECT_UNLOCK (sink);
}
