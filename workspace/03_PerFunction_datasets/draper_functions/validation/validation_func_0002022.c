gst_base_sink_flush_start (GstBaseSink * basesink, GstPad * pad)
{


  gst_base_sink_set_flushing (basesink, pad, TRUE);


  GST_PAD_STREAM_LOCK (pad);
  gst_base_sink_reset_qos (basesink);


  basesink->playing_async = TRUE;
  if (basesink->priv->async_enabled) {
    gst_element_lost_state (GST_ELEMENT_CAST (basesink));
  } else {


    gst_element_set_start_time (GST_ELEMENT_CAST (basesink), 0);
    basesink->priv->have_latency = TRUE;
  }
  gst_base_sink_set_last_buffer (basesink, NULL);
  GST_PAD_STREAM_UNLOCK (pad);
}
